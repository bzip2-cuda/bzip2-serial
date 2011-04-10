/* Copyright (c) 2010 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Huffman_coding_(C_Plus_Plus)?action=history&offset=20090129100015

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Huffman_coding_(C_Plus_Plus)?oldid=16057
*/

//Modified by Anirudh R and Anushree S, with thanks to the above

#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <string>

template<typename DataType, typename Frequency> class Hufftree
{
	public:
		template<typename InputIterator>
		Hufftree(InputIterator begin, InputIterator end);

		~Hufftree() { delete tree; }

		template<typename InputIterator>
		std::vector<bool> encode(InputIterator begin, InputIterator end);

		std::vector<bool> encode(DataType const& value)
		{
			return encoding[value];
		}

		template<typename OutputIterator>
		void decode(std::vector<bool> const& v, OutputIterator iter);

	private:
		class Node;
		Node* tree;

		typedef std::map<DataType, std::vector<bool> > encodemap;
		encodemap encoding;

		class NodeOrder;
};


template<typename DataType, typename Frequency>
struct Hufftree<DataType, Frequency>::Node
{
	Frequency frequency;
	Node* leftChild;
	union
	{
		Node* rightChild; // if leftChild != 0
		DataType* data;  // if leftChild == 0
	};

	Node(Frequency f, DataType d):
	frequency(f),
	leftChild(0),
	data(new DataType(d))
	{
	}

	Node(Node* left, Node* right):
	frequency(left->frequency + right->frequency),
	leftChild(left),
	rightChild(right)
	{
	}

	~Node()
	{
		if (leftChild)
		{
			delete leftChild;
			delete rightChild;
		}
		else
		{
			delete data;
		}
	}

	void fill(std::map<DataType, std::vector<bool> >& encoding,
	std::vector<bool>& prefix)
	{
	if (leftChild)
	{
		prefix.push_back(0);
		leftChild->fill(encoding, prefix);
		prefix.back() = 1;
		rightChild->fill(encoding, prefix);
		prefix.pop_back();
	}
	else
		encoding[*data] = prefix;
	}
};

template<typename DataType, typename Frequency>
template<typename InputIterator>
Hufftree<DataType, Frequency>::Hufftree(InputIterator begin, InputIterator end):
tree(0)
{
	std::priority_queue<Node*, std::vector<Node*>, NodeOrder> pqueue;

	while (begin != end)
	{
		Node* dataNode = new Node(begin->second, begin->first);
		pqueue.push(dataNode);
		++begin;
	}

	while (!pqueue.empty())
	{
		Node* top = pqueue.top();
		pqueue.pop();
		if (pqueue.empty())
		{
			tree = top;
		}
		else
		{
			Node* top2 = pqueue.top();
			pqueue.pop();
			pqueue.push(new Node(top, top2));
		}
	}

	std::vector<bool> bitvec;
	tree->fill(encoding, bitvec);

}

template<typename DataType, typename Frequency>
struct Hufftree<DataType, Frequency>::NodeOrder
{
	bool operator()(Node* a, Node* b)
	{
		if (b->frequency < a->frequency)
			return true;
		if (a->frequency < b->frequency)
			return false;

		if (!a->leftChild && b->leftChild)
			return true;
		if (a->leftChild && !b->leftChild)
			return false;

		if (a->leftChild && b->leftChild)
		{
			if ((*this)(a->leftChild, b->leftChild))
				return true;
			if ((*this)(b->leftChild, a->leftChild))
				return false;
			return (*this)(a->rightChild, b->rightChild);
		}

		return *(a->data) < *(b->data);

	}
};

template<typename DataType, typename Frequency>
template<typename InputIterator>
std::vector<bool> Hufftree<DataType, Frequency>::encode(InputIterator begin, InputIterator end)
{
	std::vector<bool> result;
	while (begin != end)
	{
		typename encodemap::iterator i = encoding.find(*begin);
		result.insert(result.end(), i->second.begin(), i->second.end());
		++begin;
	}
	return result;
}

template<typename DataType, typename Frequency>
template<typename OutputIterator>
void Hufftree<DataType, Frequency>::decode(std::vector<bool> const& v, OutputIterator iter)
{
	Node* node = tree;
	for (std::vector<bool>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		node = *i? node->rightChild : node->leftChild;
		if (!node -> leftChild)
		{
			*iter++ = *(node->data);
			node = tree;
		}
	}
}

std::ostream& operator<<(std::ostream& os, std::vector<bool> vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<bool>(os, ""));
	return os;
}

int main()
{
	std::map<char, double> frequencies;
		frequencies['e'] = 0.124167;
		frequencies['a'] = 0.0820011;
		frequencies['t'] = 0.0969225;
		frequencies['i'] = 0.0768052;
		frequencies['n'] = 0.0764055;
		frequencies['o'] = 0.0714095;
		frequencies['s'] = 0.0706768;
		frequencies['r'] = 0.0668132;
		frequencies['l'] = 0.0448308;
		frequencies['d'] = 0.0363709;
		frequencies['h'] = 0.0350386;
		frequencies['c'] = 0.0344391;
		frequencies['u'] = 0.028777;
		frequencies['m'] = 0.0281775;
		frequencies['f'] = 0.0235145;
		frequencies['p'] = 0.0203171;
		frequencies['y'] = 0.0189182;
		frequencies['g'] = 0.0181188;
		frequencies['w'] = 0.0135225;
		frequencies['v'] = 0.0124567;
		frequencies['b'] = 0.0106581;
		frequencies['k'] = 0.00393019;
		frequencies['x'] = 0.00219824;
		frequencies['j'] = 0.0019984;
		frequencies['q'] = 0.0009325;
		frequencies['z'] = 0.000599;

	Hufftree<char, double> hufftree(frequencies.begin(), frequencies.end());

	for (char ch = 'a'; ch <= 'z'; ++ch)
	{
		std::cout << ch << ": " << hufftree.encode(ch) << "\n";
	}

	std::string source = "bananas";

	std::cout << source << "\n";

	std::vector<bool> encoded = hufftree.encode(source.begin(), source.end());
	std::cout << encoded << "\n";

	std::string destination;
	hufftree.decode(encoded, std::back_inserter(destination));
	std::cout << destination << "\n";

}
