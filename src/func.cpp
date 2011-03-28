#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ostream>
#include <iterator>

using namespace std;

void bwt(string word, vector<string> &rotations)
{
	int len, i, j;
	
	rotations.push_back (word);
	len  = word.length();
	
	for (i = 1; i < len; i++)
	{	
		string rot_word;
		rot_word.append(word.substr(i, len -1));
		rot_word.append(word.substr(0, i));
		rotations.push_back (rot_word);
	}
	
	sort (rotations.begin(), rotations.end());
	
	return rotations;
}

void mtf(string word, string &list)
{
	int counter, index;
	for (counter = 0; counter != 256; counter++)
	{
		string list1;
		list1 = char(counter);
		list = list + list1;
	}
	
	for (counter = 0; counter < word.length(); counter++)
	{
		for (index = 0; ; index++)
		{
			if (word[counter] == list[index])
				break;
		}
		
		for ( ; index != 0; index--)
		{	
			list[index] = list[index-1];
		}
		list[0] = word[counter];
	}
}

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

template<typename DataType, typename Frequency> struct Hufftree<DataType, Frequency>::Node
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

void readFile(string &line) //have to replace getline with something more feasible.
{
    if (argc < 2) { help(argv[0]); return 1; }
    std::vector<std::string> file;
    file.clear();
    std::ifstream infile (argv[1], std::ios_base::in);
    while (getline(infile, line, '\n'))
    {
        file.push_back (line);
    }

    //std::cout << "Read " << file.size() << " lines.\n";
}
