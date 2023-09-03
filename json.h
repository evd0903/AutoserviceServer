#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include <cassert>
#include <cctype>
#include <optional>

namespace json {

	class Node;
	class Document;
	using Dict = std::map<std::string, Node>;
	using Array = std::vector<Node>;
	using Number = std::variant<int, double>;

	class ParsingError : public std::runtime_error {
	public:
		using runtime_error::runtime_error;
	};

	class Node {
	public:
		Node() = default;
		Node(nullptr_t) { item_ = {}; }
		Node(Array array);
		Node(Dict map);
		Node(int value);
		Node(double value);
		Node(bool value);
		Node(std::string value);

		const Array& AsArray() const;
		const Dict& AsMap() const;
		int AsInt() const;
		const std::string& AsString() const;
		double AsDouble() const;
		bool AsBool() const;

		bool IsNull() const;
		bool IsInt() const;
		bool IsDouble() const;
		bool IsPureDouble() const;
		bool IsString() const;
		bool IsBool() const;
		bool IsArray() const;
		bool IsMap() const;

		const std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>& GetItem() const {
			return item_;
		}

		std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>& GetItem() {
			return item_;
		}

	private:
		std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string> item_;
	};

	class Document {
	public:
		Document(Node root);

		const Node& GetRoot() const;

	private:
		Node root_;
	};

	bool operator==(const Node& l, const Node& r);

	bool operator==(const Document& l, const Document& r);

	bool operator!=(const Document& l, const Document& r);

	bool operator!=(const Node& l, const Node& r);

	Document Load(std::istream& input);

	Number LoadNumber(std::istream& input);

	void Print(const Document& doc, std::ostream& output);

}