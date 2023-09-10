#include "json_builder.h"

using namespace std;

namespace json {

	Node& Builder::Build()
	{
		if (nodes_.empty() || !node_stack_.empty()) {
			throw logic_error("");
		}
		return root_;
	}

	Builder& Builder::Key(std::string key)
	{
		if (node_stack_.empty() || !node_stack_.back()->IsDict()) {
			throw logic_error("");
		}
		Node node = key;
		nodes_.push(move(node));
		node_stack_.push_back(&nodes_.top());
		return *this;
	}

	Builder& Builder::Value(Node value)
	{
		if (node_stack_.empty()) {
			if (!nodes_.empty()) {
				throw logic_error("");
			}
			nodes_.push(value);
			root_ = value;
		}
		else if (node_stack_.back()->IsArray()) {
			Array& arr = const_cast<Array&>(node_stack_.back()->AsArray());
			arr.push_back(value);

		}
		else {
			string key = node_stack_.back()->AsString();
			node_stack_.pop_back();
			nodes_.pop();
			Dict& dict = const_cast<Dict&>(node_stack_.back()->AsDict());
			dict[key] = value;
		}
		return *this;
	}

	DictItemContext Builder::StartDict()
	{
		if (!nodes_.empty() && node_stack_.empty()) {
			throw logic_error("");
		}
		Node node = Dict{};
		nodes_.push(move(node));
		node_stack_.emplace_back(&nodes_.top());


		return  { *this };

	}

	ArrayItemContext Builder::StartArray()
	{
		if (!nodes_.empty() && node_stack_.empty()) {
			throw logic_error("");
		}
		nodes_.push(Array{});
		node_stack_.emplace_back(&nodes_.top());
		return { *this };
	}

	Builder& Builder::EndDict()
	{
		if (node_stack_.empty() || !node_stack_.back()->IsDict()) {
			throw logic_error("");
		}
		Dict dict = node_stack_.back()->AsDict();
		node_stack_.pop_back();
		nodes_.pop();
		return Value(move(dict));
	}

	Builder& Builder::EndArray()
	{
		if (node_stack_.empty() || !node_stack_.back()->IsArray()) {
			throw logic_error("");
		}
		Array arr = node_stack_.back()->AsArray();
		node_stack_.pop_back();
		nodes_.pop();
		return Value(move(arr));
	}

	DictItemContext::DictItemContext(Builder& item) : builder_(item)
	{
	}

	ItemContextAfterKey DictItemContext::Key(std::string key)
	{
		return builder_.Key(key);
	}

	Builder& DictItemContext::EndDict()
	{
		return builder_.EndDict();
	}

	ArrayItemContext::ArrayItemContext(Builder& item) : builder_(item)
	{
	}

	ItemContextAfterValueOfArray ArrayItemContext::Value(Node node)
	{
		builder_.Value(node);
		return { builder_ };
	}

	DictItemContext ArrayItemContext::StartDict()
	{
		return builder_.StartDict();
	}

	ArrayItemContext ArrayItemContext::StartArray()
	{
		return builder_.StartArray();
	}

	Builder& ArrayItemContext::EndArray()
	{
		return builder_.EndArray();
	}

	ItemContextAfterKey::ItemContextAfterKey(Builder& item) : builder_(item)
	{
	}

	DictItemContext ItemContextAfterKey::Value(Node node)
	{
		builder_.Value(node);
		return { builder_ };
	}

	DictItemContext ItemContextAfterKey::StartDict()
	{
		return builder_.StartDict();
	}

	ArrayItemContext ItemContextAfterKey::StartArray()
	{
		return builder_.StartArray();
	}

	ItemContextAfterValueOfArray::ItemContextAfterValueOfArray(Builder& item) : builder_(item)
	{
	}

	ItemContextAfterValueOfArray ItemContextAfterValueOfArray::Value(Node node)
	{
		builder_.Value(node);
		return { builder_ };
	}

	DictItemContext ItemContextAfterValueOfArray::StartDict()
	{
		return builder_.StartDict();
	}

	ArrayItemContext ItemContextAfterValueOfArray::StartArray()
	{
		return builder_.StartArray();
	}

	Builder& ItemContextAfterValueOfArray::EndArray()
	{
		return builder_.EndArray();
	}

}