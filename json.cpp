#include "json.h"

using namespace std;

namespace json {

	namespace {

		Node LoadNode(istream& input);

		Node LoadArray(istream& input) {
			Array result;

			for (char c; input >> c && c != ']';) {
				if (c != ',') {
					input.putback(c);
				}
				result.push_back(LoadNode(input));
			}

			return Node(move(result));
		}

		Node LoadString(istream& input) {
			string line;
			char c;
			while (input.get(c)) {
				if (c == '\"') {
					break;
				}
				if (c == '\\') {
					input.get(c);
					if (!input.eof()) {
						switch (c)
						{
						case '\"':
							line += '\"';
							break;
						case '\\':
							line += '\\';
							break;
						case 'n':
							line += '\n';
							break;
						case 't':
							line += '\t';
							break;
						case 'r':
							line += '\r';
							break;
						default:
							throw ParsingError(" "s);
							break;
						}
					}
				}
				else {
					line += c;
				}
			}
			if (input.eof()) {
				throw ParsingError(" "s);
			}
			return Node(move(line));
		}

		Node LoadDict(istream& input) {
			Dict result;

			for (char c; input >> c && c != '}';) {
				if (c == ',') {
					input >> c;
				}

				string key = LoadString(input).AsString();
				input >> c;
				result.insert({ move(key), LoadNode(input) });
			}

			return Node(move(result));
		}

		Node LoadNode(istream& input) {
			char c;
			input >> c;

			if (c == EOF) {
				throw ParsingError(" "s);
			}

			if (c == '[') {
				input >> c;
				if (input.eof())
					throw ParsingError(" "s);
				input.unget();
				return LoadArray(input);
			}
			else if (c == '{') {
				input >> c;
				if (input.eof())
					throw ParsingError(" "s);
				input.unget();
				return LoadDict(input);
			}
			else if (c == '"') {
				return LoadString(input);
			}
			else if (c == 't' || c == 'f' || c == 'n') {
				input.putback(c);
				string s;
				while (isalpha(input.peek())) {
					s += static_cast<char>(input.get());
				}

				if (s == "true"s) {
					return Node{ true };
				}
				else if (s == "false"s) {
					return Node{ false };
				}
				else if (s == "null"s) {
					return Node();
				}
				else {
					throw ParsingError(" "s);
				}
			}
			else {
				input.putback(c);
				Number num = LoadNumber(input);
				if (get_if<int>(&num)) {
					return Node(get<int>(num));
				}
				else {
					return Node(get<double>(num));
				}
			}

		}

	}

	Node::Node(Array array)
		: item_(move(array)) {
	}

	Node::Node(Dict map)
		: item_(move(map)) {
	}

	Node::Node(int value) {
		item_ = value;
	}

	Node::Node(double value) {
		item_ = value;
	}

	Node::Node(bool value) {
		item_ = value;
	}

	Node::Node(string value)
		: item_(move(value)) {
	}

	const Array& Node::AsArray() const {
		if (!IsArray()) {
			throw std::invalid_argument(" "s);
		}
		return get<Array>(item_);
	}

	const Dict& Node::AsMap() const {
		if (!IsMap()) {
			throw std::invalid_argument(" "s);
		}
		return get<Dict>(item_);
	}

	int Node::AsInt() const {
		if (!IsInt()) {
			throw std::invalid_argument(" "s);
		}
		return get<int>(item_);
	}

	double Node::AsDouble() const {
		if (!IsDouble()) {
			throw std::logic_error(" "s);
		}
		return IsPureDouble() ? get<double>(item_) : static_cast<double>(AsInt());
	}

	bool Node::AsBool() const {
		if (!IsBool()) {
			throw std::invalid_argument(" "s);
		}
		return get<bool>(item_);
	}

	bool Node::IsNull() const {
		return holds_alternative<std::nullptr_t>(item_);
	}

	bool Node::IsInt() const {
		return holds_alternative<int>(item_);
	}

	bool Node::IsDouble() const {
		return IsInt() || IsPureDouble();
	}

	bool Node::IsPureDouble() const {
		return holds_alternative<double>(item_);
	}

	bool Node::IsString() const {
		return holds_alternative<string>(item_);
	}

	bool Node::IsBool() const {
		return holds_alternative<bool>(item_);
	}

	bool Node::IsArray() const {
		return holds_alternative<Array>(item_);
	}

	bool Node::IsMap() const {
		return holds_alternative<Dict>(item_);
	}

	const string& Node::AsString() const {
		if (!IsString()) {
			throw std::invalid_argument(" "s);
		}
		return get<string>(item_);
	}

	Document::Document(Node root)
		: root_(move(root))
	{
	}

	const Node& Document::GetRoot() const {
		return root_;
	}

	Document Load(istream& input) {
		return Document{ LoadNode(input) };
	}

	Number LoadNumber(std::istream& input) {
		using namespace std::literals;

		std::string parsed_num;

		auto read_char = [&parsed_num, &input] {
			parsed_num += static_cast<char>(input.get());
			if (!input) {
				throw ParsingError("Failed to read number from stream"s);
			}
		};

		auto read_digits = [&input, read_char] {
			if (!std::isdigit(input.peek())) {
				throw ParsingError("A digit is expected"s);
			}
			while (std::isdigit(input.peek())) {
				read_char();
			}
		};

		if (input.peek() == '-') {
			read_char();
		}

		if (input.peek() == '0') {
			read_char();
		}
		else {
			read_digits();
		}

		bool is_int = true;
		if (input.peek() == '.') {
			read_char();
			read_digits();
			is_int = false;
		}

		if (int ch = input.peek(); ch == 'e' || ch == 'E') {
			read_char();
			if (ch = input.peek(); ch == '+' || ch == '-') {
				read_char();
			}
			read_digits();
			is_int = false;
		}

		try {
			if (is_int) {
				try {
					return std::stoi(parsed_num);
				}
				catch (...) {

				}
			}
			return std::stod(parsed_num);
		}
		catch (...) {
			throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
		}
	}

	void Print(const Document& doc, std::ostream& output) {
		if (doc.GetRoot().IsNull()) {
			output << "null"s;
		}
		if (doc.GetRoot().IsInt()) {
			output << doc.GetRoot().AsInt();
		}
		if (doc.GetRoot().IsPureDouble()) {
			output << doc.GetRoot().AsDouble();
		}
		if (doc.GetRoot().IsBool()) {
			output << boolalpha << doc.GetRoot().AsBool();
		}
		if (doc.GetRoot().IsString()) {
			output << "\""s;
			for (char c : doc.GetRoot().AsString()) {
				switch (c)
				{
				case '\"':
					output << "\\\"";
					break;
				case '\n':
					output << "\\n";
					break;
				case '\t':
					output << "\\t";
					break;
				case '\r':
					output << "\\r";
					break;
				case '\\':
					output << "\\\\";
					break;
				default:
					output << c;
					break;
				}

			}
			output << "\""s;
		}

		if (doc.GetRoot().IsArray()) {
			auto arr = doc.GetRoot().AsArray();
			output << "["s;
			for (size_t i = 0; i < arr.size(); ++i) {
				Print(Document{ arr[i] }, output);
				if (i != arr.size() - 1) {
					output << ","s;
				}
			}
			output << "]"s;
		}
		if (doc.GetRoot().IsMap()) {
			auto dict = doc.GetRoot().AsMap();
			output << "{"s;
			for (auto&[key, value] : dict) {
				Print(Document{ key }, output);
				output << ":"s;
				Print(Document{ value }, output);
				if (dict.find(key) != --dict.end()) {
					output << ","s;
				}
			}
			output << "}"s << endl;
		}
	}

	bool operator==(const Node& l, const Node& r) {
		return l.GetItem() == r.GetItem();
	}

	bool operator!=(const Node& l, const Node& r) {
		return !(l == r);
	}

	bool operator==(const Document& l, const Document& r) {
		return l.GetRoot() == r.GetRoot();
	}

	bool operator!=(const Document& l, const Document& r) {
		return !(l == r);
	}

}