#pragma once

#include <stack>

#include "json.h"

namespace json {

	class Builder;

	class DictItemContext;

	class ArrayItemContext;

	class ItemContextAfterKey {
	public:
		ItemContextAfterKey(Builder& item);

		DictItemContext Value(Node node);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

	private:
		Builder& builder_;
	};

	class DictItemContext {
	public:
		DictItemContext(Builder& item);

		ItemContextAfterKey Key(std::string);

		Builder& EndDict();

	private:
		Builder& builder_;
	};

	class ItemContextAfterValueOfArray
	{
	public:
		ItemContextAfterValueOfArray(Builder& item);

		ItemContextAfterValueOfArray Value(Node node);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

		Builder& EndArray();

	private:
		Builder& builder_;
	};

	class ArrayItemContext {
	public:
		ArrayItemContext(Builder& item);

		ItemContextAfterValueOfArray Value(Node node);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

		Builder& EndArray();

	private:
		Builder& builder_;
	};

	class Builder {
	public:
		Builder() = default;

		Node& Build();

		Builder& Key(std::string);

		Builder& Value(Node);

		DictItemContext StartDict();

		ArrayItemContext StartArray();

		Builder& EndDict();

		Builder& EndArray();

	private:
		Node root_;
		std::vector<Node*> node_stack_;
		std::stack<Node> nodes_;

	};

}