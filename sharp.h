#ifndef SHARP_H_INCLUDED
#define SHARP_H_INCLUDED

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::to_string;
using std::make_shared;
using std::tuple;

constexpr unsigned indent = 2;

string EmptyString(unsigned long d);


enum class DEGREE
{
    ZERO, ONE, TWO, TWOLEFT
};

class Level_322_Desc;
class PartialLevelOneTree;
class PartialLevel_leq_2_Tree;


template <typename TYPE>
class TreeNode;
template <typename TYPE>
class Tree;


template<typename ENTRYTYPE, typename VALUETYPE>
using FuncTreeNode = TreeNode<pair<ENTRYTYPE,VALUETYPE>>;
template <typename ENTRYTYPE, typename VALUETYPE>
class FuncTree;

typedef vector<unsigned long>
SingleSequence;
typedef vector<SingleSequence>
DoubleSequence;


typedef pair<int, SingleSequence>
MixedType;



typedef TreeNode<unsigned long>
LevelOneTreeNode;
class LevelOneTree;

typedef FuncTreeNode<unsigned long, SingleSequence>
LevelOneFactorNode;
typedef FuncTree<unsigned long, SingleSequence>
LevelOneFactor;


typedef FuncTreeNode <SingleSequence, PartialLevelOneTree>
LevelTwoTreeNode;
class LevelTwoTree;

template <typename A>
class LevelTwoTreeBasedDesc;

typedef LevelTwoTreeBasedDesc<SingleSequence>
Level_21_Desc;

typedef LevelTwoTreeBasedDesc<Level_21_Desc>
Level_221_Desc;

typedef pair<int, Level_21_Desc>
MixedType2;

string String (const Level_21_Desc & D);

template <typename T>
bool operator == (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator <= (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator >= (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator < (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator > (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator != (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
template <typename T>
bool operator == (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
template <typename T>
bool operator <= (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
template <typename T>
bool operator >= (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
template <typename T>
bool operator < (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
template <typename T>
bool operator > (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
template <typename T>
bool operator != (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;


//define the BK order
template <typename TYPE>
bool operator < (const vector<TYPE> & q, const vector<TYPE> & p)
{
    auto a = q.cbegin();
    auto b = p.cbegin();

    while ( a!= q.cend()  && b != p.cend())
    {
        if (*a != *b)
        {
            break;
        }
        ++a;
        ++b;
    }
    if ( a == q.cend())
    {
        return false;
    }
    if (b == p.cend())
    {
        return true;
    }
    return *a < *b;
}


template <typename TYPE>
bool operator <=  (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return (p<q) || (p == q);
}

template <typename TYPE>
bool operator >  (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return !(p<=q);
}

template <typename TYPE>
bool operator >=  (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return !(p<q);
}



string EmptyString(unsigned long d)
{
    return string(d, ' ');
}


string String (const unsigned long & k)
{
    return to_string (k);
}

string String (const vector<unsigned long> & k)
{

    if (k.empty() )
    {
        return "()";
    }
    string output = "(";
    for (auto && i : k)
    {
        output += to_string(i) + " ";
    }
    output.pop_back();
    output += ")";
    return output;
}


string String (const vector<vector<unsigned long>> & k)
{
    if (k.empty())
    {
        return "()";
    }
    string output = "(";
    for (auto && i : k)
    {
        output += String(i) + " ";
    }
    output.pop_back();
    output += ")";
    return output;
}


string String (const vector<tuple<int,SingleSequence,SingleSequence>> & r)
{
    string output;
    for (auto && i : r)
    {
        if (std::get<0> (i) == 2)
        {
            output += String(std::get<2> (i));
        }
        else if (std::get<0>(i) == 1){
            output += String(std::get<1> (i));
        }
        else
        {
            output += "-1";
        }
    }
    return output;
}

string String (const vector<tuple<int,SingleSequence,Level_21_Desc>> & r);



template <typename TYPE>
class TreeNode
// a general template for a treenode. The entry has type <TYPE>
{
    template <typename>
    friend class Tree;
    template <typename, typename>
    friend class FuncTree;
    friend class LevelOneTree;
    friend class LevelTwoTree;

private:
    TYPE                    entry;

    TreeNode *              parent;

    unsigned long           number_of_children;
    TreeNode *              first_child;
    TreeNode *              last_child;

    TreeNode *              left;
    TreeNode *              right;
    TreeNode *              BKleft;
    TreeNode *              BKright;

public:

    ~TreeNode(){}

    TreeNode    ( ) :
        // by default, creates the empty node
        // for convenience , even empty node has a entry to default TYPE

        entry                   (TYPE ()),
        parent                  (nullptr),
        number_of_children      (0),
        first_child             (nullptr),
        last_child              (nullptr),
        left                    (nullptr),
        right                   (nullptr),
        BKleft                  (nullptr),
        BKright                 (nullptr)
    {}
    TreeNode    ( const TYPE & e ) :

        entry                   (e),
        parent                  (nullptr),
        number_of_children      (0),
        first_child             (nullptr),
        last_child              (nullptr),
        left                    (nullptr),
        right                   (nullptr),
        BKleft                  (nullptr),
        BKright                 (nullptr)
    {}


    TreeNode(const TreeNode & s) :
        //only copy the entry of s, the number of children of s
        entry                   (s.entry),
        parent                  (nullptr),
        number_of_children      (s.number_of_children),
        first_child             (nullptr),
        last_child              (nullptr),
        left                    (nullptr),
        right                   (nullptr),
        BKleft                  (nullptr),
        BKright                 (nullptr)
    {}

    const TYPE & Entry() const
    {
        return entry;
    }

    //compare the entries, provided TYPE can be compared
    //
    bool  operator == (const TreeNode & p) const
    {
        return entry == p.entry;
    }
    bool  operator != (const TreeNode & p) const
    {
        return entry != p.entry;
    }
    bool  operator < (const TreeNode & p) const
    {
        return entry < p.entry;
    }
    bool  operator > (const TreeNode & p) const
    {
        return entry > p.entry;
    }
    bool  operator <= (const TreeNode & p) const
    {
        return entry <= p.entry;
    }
    bool  operator >= (const TreeNode & p) const
    {
        return entry >= p.entry;
    }


    void MakeEntry(const TYPE & e)
    {
        entry = e;
    }

    bool IsLastBitLeftMost() const
    {
        return left == nullptr;
    }

    /*
        bool IsEveryBitLeftMost() const
        {
            const TreeNode<TYPE> * current = this;
            while (current->IsNonEmpty())
            {
                if (!(current->IsLastBitLeftMost()))
                {
                    return false;
                }
                current = current->parent;
            }
            return true;
        }*/

    bool IsLastBitRightMost() const
    {
        return right == nullptr;
    }
    bool IsBKLeftMost() const
    {
        return BKleft == nullptr;
    }
    bool HasChild() const
    {
        return number_of_children > 0;
    }
    bool IsTerminal() const
    {
        return number_of_children == 0;
    }

    bool IsEmpty() const
    {
        return parent == nullptr;
    }
    // is this node empty, i.e. the root?

    bool IsNonEmpty() const
    {
        return parent != nullptr;
    }

    TreeNode * BKLeft() const
    {
        return BKleft;
    }
    TreeNode * BKRight() const
    {
        return BKright;
    }
    TreeNode * Left() const
    {
        return left;
    }
    TreeNode * Right() const
    {
        return right;
    }
    TreeNode * FirstChild() const
    {
        return first_child;
    }
    TreeNode * LastChild() const
    {
        return last_child;
    }
    TreeNode * Parent() const
    {
        return parent;
    }
    const unsigned long & NumberOfChildren() const
    {
        return number_of_children;
    }
};


template <typename TYPE>
class Tree
// a template for a __nonempty__ tree whose entries have type <TYPE>
//
{
    template<typename,typename>
    friend class FuncTree;

private:

    unsigned long cardinality;
    TreeNode<TYPE> * root;

    Tree (unsigned long c, TreeNode<TYPE> * r ) :
        cardinality(c),
        root (r){}


// make "newnode" a new child below s, on the rightmost
// assuming "newnode" has every pointer to nullptr and number_of_children 0
// i.e. from initialization with an entry only
//
    void MakeNewChildBelow (TreeNode<TYPE> * const s,
                            TreeNode<TYPE> * const newnode)
    {
        ++ cardinality;

        newnode->parent = s;
        ++ s->number_of_children ;

        if (s->IsNonEmpty())
        {
            newnode->BKright = s;

            if (!(s->IsBKLeftMost()))
            {
                newnode->BKleft = s->BKleft;
                s->BKleft->BKright = newnode;
            }

            s->BKleft = newnode;
        }

        else if (s->number_of_children > 1)
        {

            newnode->BKleft = s->last_child;
            s->last_child->BKright = newnode;
            newnode->BKright = s;
            s->BKleft = newnode;
        }
        else
        {
            newnode->BKright = s;
            s->BKleft = newnode;
        }

        if (s->number_of_children == 1)
        {
            s->first_child = newnode;
            s->last_child = newnode;
        }
        else
        {
            s->last_child->right = newnode;
            newnode->left = s->last_child;
        }

        s->last_child = newnode;
    }


// make "newnode" a new node on the left of s
// assuming of course s is not root

    void MakeNewSiblingLeft(TreeNode<TYPE> * const s,
                            TreeNode<TYPE> * const newnode)
    {
        ++ cardinality;


        // set new number of children
        ++ s->parent->number_of_children;



        //starting setting the BK order
        // move alongs s upwards to the place with a elder sister, if possible
        auto current = s;
        while (current->IsNonEmpty())
        {
            if (current->IsLastBitLeftMost())
            {
                current = current->parent;
            }
            else
            {
                break;
            }
        }
        if (current->IsEmpty())
        {
            //every bit of sis smallest
            // newnode is the new smallest
            auto tempsmallest = SmallestNode();

            newnode->BKright = tempsmallest;
            tempsmallest->BKleft = newnode;
        }
        else
        {
            auto tempBKleft = current->left;
            // newnode is immediately BKright of tempBKleft

            newnode->BKleft = tempBKleft;
            newnode->BKright = tempBKleft->BKright;

            tempBKleft->BKright->BKleft = newnode;
            tempBKleft->BKright = newnode;
        }
        //finished setting BK order

        // starting set parent
        TreeNode<TYPE> * parent = s->parent;
        newnode->parent = parent;


        // starting setting sibling order and parent's first child
        if (s->left == nullptr)
        {
            //s is the first child
            newnode->right = s;
            s->left = newnode;
            parent->first_child = newnode;
        }
        else
        {
            // s is not the first child
            newnode->left = s->left;
            s->left->right = newnode;

            newnode->right = s;
            s->left = newnode;
        }
    }



public:

    friend void swap (Tree & S, Tree & T){
        std::swap(S.root,T.root);
        std::swap(S.cardinality, T.cardinality);
    }

    Tree (Tree && T) :
        cardinality(0),
        root(nullptr){
        swap(*this,T);
        }

  Tree& operator = (Tree T){
        swap(*this,T);
        return *this;
   }

  //  {

  //  return *this;}

    Tree(const TYPE & root_entry = TYPE() ):
        cardinality (1) ,
        root(new TreeNode<TYPE> (root_entry))
    {}
    // by default, cardinality is the smallest possible (1),
    // and root_entry is either provided or the default TYPE

    Tree(const Tree & T) :
        // copy the tree T
        cardinality (T.cardinality)
    {
        vector<const TreeNode<TYPE> * > a;
        vector<TreeNode<TYPE> * > b;
        a.reserve(T.cardinality);
        b.reserve(T.cardinality);
        const TreeNode<TYPE> * current (T.Root());
        while(current != nullptr)
        {
            a.emplace_back(current);
            b.emplace_back(new TreeNode<TYPE> (*current));
            // copy the entries and number_of_children first
            current = current->BKleft;
        }

        //set links between nodes
        for (unsigned long i = 0; i < T.cardinality; ++i)
        {
            for (unsigned long j = 0; j < T.cardinality; ++j)
            {
                if (a[i]->parent == a[j])
                {
                    b[i]->parent = b[j];
                }
                if (a[i]->left == a[j])
                {
                    b[i]->left = b[j];
                }
                if (a[i]->right == a[j])
                {
                    b[i]->right = b[j];
                }
                if (a[i]->BKleft == a[j])
                {
                    b[i]->BKleft = b[j];
                }
                if (a[i]->BKright == a[j])
                {
                    b[i]->BKright = b[j];
                }
                if (a[i]->first_child == a[j])
                {
                    b[i]->first_child = b[j];
                }
                if (a[i]->last_child == a[j])
                {
                    b[i]->last_child = b[j];
                }
            }
        }

        root = b[0];
        //point the root to the copied root

    }
    // finish defining copy constructor

    //destroy the tree
    ~Tree()
    {
        if (root == nullptr){
            return;
        }
        auto to_delete = SmallestNode();
        auto next = to_delete->BKright;
        while (next != nullptr)
        {
            delete to_delete;
            to_delete = next;
            next = next->BKright;
        }
        delete root;
    }


    unsigned long Length(const TreeNode<TYPE>* const s) const
    {
        return EntireEntry(s).size();
    }

    vector<TYPE> EntireEntry(const TreeNode<TYPE>* const s) const
    {
        auto output = vector<TYPE> ();
        auto current = s;
        while (current->IsNonEmpty())
        {
            output.emplace_back(current->Entry());
            current = current->parent;
        }
        reverse(output.begin(), output.end());
        return output;
    }

    string String(const TreeNode<TYPE>* const s) const
    // writes the entry of s into a string
    {
        auto h = EntireEntry(s);
        if (h.size() == 0)
        {
            return "()";
        }
        string output = "(";
        for (auto && i : h)
        {
            output += ::String(i) + " ";
        }
        output.pop_back();
        output += ")";
        return output;
    }


    void Show(const TreeNode<TYPE>* const s) const
    {
        cout<<"Node: "<<String(s)<<endl;
        cout<<"number of children: "<<s->number_of_children<<endl;
        if (s->BKleft == nullptr)
        {
            cout<< "  BKleft is nullptr"<<endl;
        }
        else
        {
            cout<<"  BKleft: "<<String(s->BKleft)<<endl;
        }
        if (s->BKright == nullptr)
        {
            cout<< "  BKright is nullptr"<<endl;
        }
        else
        {
            cout<<"  BKright: "<<String(s->BKright)<<endl;
        }
        if (s->parent == nullptr)
        {
            cout<< "  parent is nullptr"<<endl;
        }
        else
        {
            cout<<"  parent: "<<String(s->parent)<<endl;
        }
        if (s->first_child == nullptr)
        {
            cout<< "  first_child is nullptr"<<endl;
        }
        else
        {
            cout<<"  first_child: "<<String(s->first_child)<<endl;
        }
        if (s->last_child == nullptr)
        {
            cout<< "  last_child is nullptr"<<endl;
        }
        else
        {
            cout<<"  last_child: "<<String(s->last_child)<<endl;
        }
        if (s->left == nullptr)
        {
            cout<< "  left is nullptr"<<endl;
        }
        else
        {
            cout<<"  left: "<<String(s->left)<<endl;
        }
        if (s->right == nullptr)
        {
            cout<< "  right is nullptr"<<endl;
        }
        else
        {
            cout<<"  right: "<<String(s->right)<<endl;
        }
    }

    void ShowDomain(const TreeNode<TYPE>* const s) const
    {
        cout<<"Node: "<<::String(s->entry.first)<<endl;
        cout<<"number of children: "<<s->number_of_children<<endl;
        if (s->BKleft == nullptr)
        {
            cout<< "  BKleft is nullptr"<<endl;
        }
        else
        {
            cout<<"  BKleft: "<<::String(s->BKleft->entry.first)<<endl;
        }
        if (s->BKright == nullptr)
        {
            cout<< "  BKright is nullptr"<<endl;
        }
        else
        {
            cout<<"  BKright: "<<::String(s->BKright->entry.first)<<endl;
        }
        if (s->parent == nullptr)
        {
            cout<< "  parent is nullptr"<<endl;
        }
        else
        {
            cout<<"  parent: "<<::String(s->parent->entry.first)<<endl;
        }
        if (s->first_child == nullptr)
        {
            cout<< "  first_child is nullptr"<<endl;
        }
        else
        {
            cout<<"  first_child: "<<::String(s->first_child->entry.first)<<endl;
        }
        if (s->last_child == nullptr)
        {
            cout<< "  last_child is nullptr"<<endl;
        }
        else
        {
            cout<<"  last_child: "<<::String(s->last_child->entry.first)<<endl;
        }
        if (s->left == nullptr)
        {
            cout<< "  left is nullptr"<<endl;
        }
        else
        {
            cout<<"  left: "<<::String(s->left->entry.first)<<endl;
        }
        if (s->right == nullptr)
        {
            cout<< "  right is nullptr"<<endl;
        }
        else
        {
            cout<<"  right: "<<::String(s->right->entry.first)<<endl;
        }
    }


    void Show(string name = "") const
    {
        cout<<name<<" has cardinality "<< Cardinality()<<"."<<endl;
        cout<<"The nodes are:"<<endl;
        for (auto i = Root(); i != nullptr; i = NextEnumerate(i))
        {
            Show(i);
        }
    }
    void ShowDomain(string name = "") const
    {
        cout<<name<<" has cardinality "<< Cardinality()<<"."<<endl;
        cout<<"The nodes are:"<<endl;
        for (auto i = Root(); i != nullptr; i = NextEnumerate(i))
        {
            ShowDomain(i);
        }
    }


    unsigned long Cardinality() const
    {
        return cardinality;
    }

    TreeNode<TYPE> * SmallestNode() const
    // the BK-smallest node
    {
        auto current = Root();
        while (current->HasChild())
        {
            current = current->first_child;
        }
        return current;
    }

    vector<TYPE> SmallestEntry() const
    // the entire entry of the BK-smallest node
    {
        auto current = Root();
        vector<TYPE> output;
        while (current->HasChild())
        {
            current = current->first_child;
            output . emplace_back( current->Entry());
        }
        return output;
    }


    TreeNode<TYPE> * Root() const
    // the root
    {
        return root;
    }

    bool IsSubTree (Tree T);

    bool operator == (const Tree & T) const
    // compare the trees
    {
        auto current = Root();
        auto compared = T.Root();

        // search by dictionary order
        while (current != nullptr)
        {
            if (current->number_of_children != compared->number_of_children)
                return false;
            if (current->entry != compared->entry)
                return false;
            //once the node under comparison agree on number of children and  entry, continue
            current = NextEnumerate(current);
            compared = NextEnumerate(compared);
            // as long as "number_of_children" agree by far, they both point to the correct nodes
        }
        return true;
        //finished comparing
    }


    bool operator != (const Tree & T) const
    {
        return !(*this == T);
    }

    bool IsTrivial() const
    {
        return root->number_of_children == 0;
    }
    // Does the tree have only the root?

    bool IsNonTrivial() const
    {
        return root->number_of_children > 0;
    }

    TreeNode<TYPE> * NextEnumerate(TreeNode<TYPE> * const s) const
    // enumerate the nodes of the tree in the dictionary order, NOT BK ORDER!
    {
        if (s->HasChild())
        {
            return s->first_child;
        }
        TreeNode<TYPE> * current = s;

        while (current->IsNonEmpty() && current->IsLastBitRightMost())
        {
            current = current->parent;
        }
        if (current->IsEmpty())
            return nullptr;

        current = current->right;
        return current;
    }

//   bool ContainsElement(const TreeNode<TYPE> * const s) const;


//   unsigned long Rank(const TreeNode<TYPE> * const s) const;


    TreeNode<TYPE> * AddChildBelow(TreeNode<TYPE> * const s,
                                   const TYPE & y)
    {
        // add a child below s with entry y
        // return the new child
        auto newnode = new TreeNode<TYPE> (y);
        MakeNewChildBelow(s, newnode);
        return newnode;
    }

    TreeNode<TYPE> * AddSiblingLeft (TreeNode<TYPE> * const s,
                                     const TYPE & y)
    {
        // add an elder sister before s with entry y
        // return the elder sister
        auto newnode = new TreeNode<TYPE> (y);
        MakeNewSiblingLeft(s, newnode);
        return newnode;
    }

    TreeNode<TYPE> * Remove (TreeNode<TYPE> * s)
    {
        // remove the terminal node , non-root , last child of parent s
        // s must be terminal and non-root, and last child of its parent
        // or the program will crash
        //
        // returns the parent of s

        --cardinality;
        // the cardinality of myself -1

        auto parent = s->parent;

        --parent->number_of_children;
        // set the number of children of parent

        //starting setting the new BK order
        if (s->BKleft == nullptr)
        {
            s->BKright->BKleft = nullptr;
        }
        else
        {
            s->BKleft->BKright = s->BKright;
            s->BKright->BKleft = s->BKleft;
        }
        //finished setting BK order

        //starting setting the children pointer of parent
        if (parent->number_of_children == 0)
        {
            parent->first_child = nullptr;
            parent->last_child = nullptr;
        }
        else
        {
            parent->last_child = s->left;
        }
        //finished setting the children pointer of parent


        // setting the sibling order
        if (s->left == nullptr)
        {
            //do nothing
        }
        else
        {
            s->left->right = nullptr;
        }
        //finished setting sibling order

        // free the memory taken by s
        delete s;

        //return the parent of the removed node
        return parent;
    }


    TreeNode<TYPE> * MyNodeImmediateExtend (const TreeNode<TYPE>* const s, const TYPE & r) const
    {
        if (s->IsTerminal())
        {
            return nullptr;
        }
        auto current = s->first_child;
        while (current != nullptr)
        {
            if (current->Entry() == r)
            {
                return current;
            }
            current = current->right;
        }
        return nullptr;
    }

    TreeNode<TYPE> * MyNode (const TreeNode<TYPE> * const r) const
    {
        return MyNode(EntireEntry(r));
    }

    TreeNode<TYPE> * MyNode (const vector<TYPE> & r) const
    {
        TreeNode<TYPE> * current = Root();
        for (auto && i : r)
        {
            current = MyNodeImmediateExtend(current, i);
            if (current == nullptr)
            {
                return nullptr;
            }
        }
        return current;
    }

    bool ContainsElement (const vector<TYPE> & r)
    {
        return MyNode(r) != nullptr;
    }

};



template <typename ENTRYTYPE, typename VALUETYPE>
string String (const TreeNode<pair<ENTRYTYPE,VALUETYPE>> & k )
{
    string output = String( k.Entry().first);
    output += "|-->";
    output += String(k.Entry().second);
    return output;
}

// a template for a node of function whose domain is a tree
// domain takes vectors of ENTRYTYPE,
// image takes VALUETYPE
//

template <typename ENTRYTYPE, typename VALUETYPE>
ENTRYTYPE LastEntryInDomain(const TreeNode<pair<ENTRYTYPE, VALUETYPE>> & T)
{
    return T.Entry().first;
}

template <typename ENTRYTYPE, typename VALUETYPE>
VALUETYPE Value(const TreeNode<pair<ENTRYTYPE, VALUETYPE>> & T)
{
    return & T.Entry().second;
}




// a template for a function whose domain is a tree
// domain takes vectors of ENTRYTYPE,
// image takes VALUETYPE
//
template <typename ENTRYTYPE, typename VALUETYPE>
class FuncTree : public Tree<pair<ENTRYTYPE, VALUETYPE>>
{
public:

    using Tree<pair<ENTRYTYPE,VALUETYPE>>::Tree;

//    VALUETYPE * Value(const Node<ENTRYTYPE> * const s) const;

//    void MakeValueAtNode(const Node<ENTRYTYPE> * const s, const VALUETYPE & y);

    // produces the domain of the function, which is a Tree<ENDRYTYPE>
    Tree<ENTRYTYPE> Domain() const
    {
        vector<const FuncTreeNode<ENTRYTYPE,VALUETYPE> * > a;
        vector<TreeNode<ENTRYTYPE> * > b;
        a.reserve(this->cardinality);
        b.reserve(this->cardinality);
        auto current = this->root;
        while(current != nullptr)
        {
            a.emplace_back(current);
            b.emplace_back(new TreeNode<ENTRYTYPE>(
                               current->Entry().first));
            b.back()->number_of_children = current->number_of_children;
            // copy the entries and number_of_children first
            current = current->BKleft;
        }

        //set links between nodes
        for (unsigned long i = 0; i < this->cardinality; ++i)
        {
            for (unsigned long j = 0; j < this->cardinality; ++j)
            {
                if (a[i]->parent == a[j])
                {
                    b[i]->parent = b[j];
                }
                if (a[i]->left == a[j])
                {
                    b[i]->left = b[j];
                }
                if (a[i]->right == a[j])
                {
                    b[i]->right = b[j];
                }
                if (a[i]->BKleft == a[j])
                {
                    b[i]->BKleft = b[j];
                }
                if (a[i]->BKright == a[j])
                {
                    b[i]->BKright = b[j];
                }
                if (a[i]->first_child == a[j])
                {
                    b[i]->first_child = b[j];
                }
                if (a[i]->last_child == a[j])
                {
                    b[i]->last_child = b[j];
                }
            }
        }

        return Tree<ENTRYTYPE>(this->cardinality, b[0]);

    }


    void MakeValueAtMyNode(TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s,
                           const VALUETYPE & y)
    {
        s->Entry()->second = y;
    }



    vector<ENTRYTYPE>   EntireEntryInDomain(
        const TreeNode<pair<ENTRYTYPE,VALUETYPE>> * const s) const
    {
        vector<ENTRYTYPE> output;
        auto current = s;
        while (current->IsNonEmpty())
        {
            output.emplace_back(LastEntryInDomain(current));
            current = current->Parent();
        }
        reverse(output.begin(), output.end());
        return output;
    }



    string StringInDomain (const FuncTreeNode<ENTRYTYPE,VALUETYPE>* const s) const
    // writes the entry of domain component of s into a string
    {
        auto && h = EntireEntryInDomain(s);
        if (h.size() == 0)
        {
            return "()";
        }
        string output = "(";
        for (auto && i : h)
        {
            output += ::String(i) + " ";
        }
        output.pop_back();
        output += ")";
        return output;
    }



    FuncTreeNode<ENTRYTYPE,VALUETYPE> *
    MyNodeInDomainImmediateExtend (const FuncTreeNode<ENTRYTYPE,VALUETYPE>* const s,
                                   const ENTRYTYPE & r) const
    {
        if (s->IsTerminal())
        {
            return nullptr;
        }
        auto current = s->FirstChild();
        while (current != nullptr)
        {
            if (LastEntryInDomain(current) == r)
            {
                return current;
            }
            current = current->Right();
        }
        return nullptr;
    }


    FuncTreeNode<ENTRYTYPE,VALUETYPE> * MyNodeInDomain (const vector<ENTRYTYPE> & r) const
    {
        auto current = this->Root();
        for (auto && i : r)
        {
            current = MyNodeInDomainImmediateExtend(current, i);
            if (current == nullptr)
            {
                return nullptr;
            }
        }
        return current;
    }

    const VALUETYPE & Value (const vector<ENTRYTYPE> & r) const
    {
        auto n = MyNodeInDomain(r);
        return Value(n);
    }

    const ENTRYTYPE & LastEntryInDomain (const FuncTreeNode<ENTRYTYPE,VALUETYPE> * s) const
    {
        return s->Entry().first;
    }

    const VALUETYPE & Value (const FuncTreeNode<ENTRYTYPE,VALUETYPE> * const s) const
    {
        return s->Entry().second;
    }

    bool ContainsElementInDomain (const vector<ENTRYTYPE> & r) const
    {
        return MyNodeInDomain(r) != nullptr;
    }

    TreeNode<pair<ENTRYTYPE,VALUETYPE>>* AddChildBelow(
                                         TreeNode<pair<ENTRYTYPE,VALUETYPE>> * const s,
                                         const ENTRYTYPE & x,
                                         const VALUETYPE & y)
    {
        return Tree<pair<ENTRYTYPE,VALUETYPE>>::AddChildBelow(
                   s, pair<ENTRYTYPE,VALUETYPE> (x,y)    );
    }

    TreeNode<pair<ENTRYTYPE,VALUETYPE>>* AddSiblingLeft(
                                         TreeNode<pair<ENTRYTYPE,VALUETYPE>> * const s,
                                         const ENTRYTYPE & x,
                                         const VALUETYPE & y)
    {
        return Tree<pair<ENTRYTYPE,VALUETYPE>>::AddSiblingLeft(
                   s, pair<ENTRYTYPE,VALUETYPE> (x,y)    );
    }
};

// a template of adding child below in a function
// based on a single tree
// just need the value
//
template <typename VALUETYPE>
FuncTreeNode<unsigned long,VALUETYPE> * AddChildBelow (
    FuncTree<unsigned long,VALUETYPE> & f,
    FuncTreeNode<unsigned long,VALUETYPE> * const s,
    const VALUETYPE & new_in_image)
{
    auto next_entry = s->NumberOfChildren();
    return f.AddChildBelow(s, next_entry, new_in_image);
}

// a template of adding child below in a function
// based on a double tree
// just need the value
//
template <typename VALUETYPE>
FuncTreeNode<SingleSequence,VALUETYPE> * AddChildBelow (
    FuncTree<SingleSequence,VALUETYPE> & f,
    FuncTreeNode<SingleSequence,VALUETYPE> * const s,
    const VALUETYPE & new_in_image)
{
    SingleSequence next_entry;
    if (s->NumberOfChildren() == 0)
    {
        next_entry = vector<unsigned long> {0};
    }
    else
    {
        auto last_child_last_entry = s->LastChild()->Entry().first;
        next_entry = vector<unsigned long> {last_child_last_entry[0]+1};
    }
    return f.AddChildBelow(s, next_entry, new_in_image);
}

bool IsProperInitialSegment (const vector<unsigned long> & a,
                             const vector<unsigned long> & b)
{

    if (a.size()>= b.size())
    {
        return false;
    }
    for (unsigned i = 0; i < a.size(); ++i)
    {
        if (a[i]!=b[i])
        {
            return false;
        }
    }
    return true;
}

// a template of adding an elder sister in a function
// based on a double tree
// just need the value
//
template <typename VALUETYPE>
FuncTreeNode<SingleSequence,VALUETYPE> * AddSiblingLeft (
    FuncTree<SingleSequence,VALUETYPE> & f,
    FuncTreeNode<SingleSequence,VALUETYPE> * const s,
    const VALUETYPE & new_in_image)
{
    SingleSequence next_entry;
    if (s->Left() == nullptr)
    {
        next_entry = s->Entry().first;
        next_entry . emplace_back(0);
    }
    else
    {
        auto left_last_entry = s->Left()->Entry().first;
        auto last_entry = s->Entry().first;
        // maybe left is one-node extension of
        // maybe not
        if (IsProperInitialSegment(last_entry, left_last_entry))
        {
            next_entry = left_last_entry;
            next_entry.back() += 1;
        }
        else
        {
            next_entry = last_entry;
            next_entry.emplace_back(0);
        }
    }
    return f.AddSiblingLeft(s, next_entry, new_in_image);
}


class LevelOneTree : public Tree<unsigned long>
{
    //a level-1 tree

public:

    LevelOneTree (const Tree& T) : Tree<unsigned long>::Tree(T) {};

    LevelOneTree () = default;

    LevelOneTree (const LevelOneTree & P) = default;

    LevelOneTree (LevelOneTree && P) :
        Tree<unsigned long>(std::move(P)) {}

    LevelOneTree & operator  = (LevelOneTree P) {
        swap(*this,P);
        return *this;
    }

    LevelOneTreeNode * AddChildBelow(LevelOneTreeNode * const s)
    {
        return Tree<unsigned long>::AddChildBelow(s, s->NumberOfChildren());
    }
    LevelOneTreeNode * AddChildBelow(const SingleSequence & s)
    {
        return AddChildBelow(MyNode(s));
    }

//   unsigned long Cardinality() const
//   {
//       return Tree<unsigned long>::Cardinality() - 1;
    //  }
    // root doesn't count in a level-1 tree

    bool IsRegular() const;
    //  TreeNode * SmallestNode() const;
//   bool ContainsElement(const TreeNode * const s) const;
//    TreeNode * NextEnumerate(TreeNode * const s) const;
    void Input(const string name = "", const unsigned long d = 0)
    {

        auto current = Root();
        cout<<EmptyString(d)<<"Input the level-1 tree "<<name<<endl;
        while (true)
        {
            cout<<EmptyString(d + indent)<<"How many immediate successors of "<<String(current)<<" ? ";
            unsigned long k;
            cin>>k;

            if (k == 0)
            {
                if (current->IsEmpty())
                {
                    cout<<EmptyString(d)<<"Level-1 tree "<<name<<" input complete!"<<endl;
                    return;
                }
                while (current->IsLastBitRightMost())
                {
                    current = current->parent;
                    if (current->IsEmpty())
                    {
                        cout<<EmptyString(d)<<"Level-1 tree "<<name<<" input complete!"<<endl;
                        return;
                    }
                }
                current = current->right;
            }
            else
            {
                for (unsigned i = 0; i < k; ++i)
                {
                    AddChildBelow(current);
                }
                current = current->first_child;
            }
        }
    }

    SingleSequence CreateNodeFromUCF (const SingleSequence & w) const
    {
        auto n = MyNode(w);
        SingleSequence output = w;
        output.emplace_back(n->NumberOfChildren());
        return output;
    }
};


class PartialLevelOneTree
{

private:

    LevelOneTree tree;
    LevelOneTreeNode * node_minus;
    // node_minus is the sequence in the tree or -1
    // the actual node is the extension of node_minus or -1
    // -1 is represented by nullptr
    //

public:
    ~PartialLevelOneTree () = default;

  /*  PartialLevelOneTree (PartialLevelOneTree&& P)
        {
        swap (*this,P);
        }

    friend void swap  (PartialLevelOneTree M, PartialLevelOneTree P){
        swap(M.tree,P.tree);
        std::swap(M.node_minus, P.node_minus);
    }

    PartialLevelOneTree& operator= (PartialLevelOneTree P){
        swap(*this,P);
        return *this;
    }*/

    PartialLevelOneTree() :
        tree (LevelOneTree ()),
        node_minus (tree.Root()) {}
    //by default, makes a tree empty and an empty node.
    // empty node is the ucf.

    PartialLevelOneTree(const PartialLevelOneTree & PP) :
        tree (PP.tree)
    {

        if (PP.node_minus == nullptr)
        {
            node_minus = nullptr;
        }
        else
        {
            node_minus = tree.MyNode(PP.node_minus);
        }
    }

    PartialLevelOneTree(const LevelOneTree & P) :
        tree(P),
        node_minus (nullptr) {}


    PartialLevelOneTree(const LevelOneTree & P, const SingleSequence & s) :
        tree(P)
    {
        node_minus = tree.MyNode(s);
    }

    bool IsTrivial() const;
    DEGREE Degree() const
    {
        return (node_minus == nullptr)? (DEGREE::ZERO) : (DEGREE::ONE);
    }

    const LevelOneTree & Tree() const
    {
        return tree;
    }

    LevelOneTreeNode * NodeMinusInTree () const
    {
        return node_minus;
    }

    SingleSequence NodeMinusSequence() const
    {
        return tree.EntireEntry(node_minus);
    }

    unsigned long Cardinality() const
    {
        return Tree().Cardinality()+1;
    }

    bool operator == (const PartialLevelOneTree & P) const
    {
        if (node_minus == nullptr && P.node_minus != nullptr)
        {
            return false;
        }
        if (node_minus != nullptr && P.node_minus == nullptr)
        {
            return false;
        }
        if (node_minus == nullptr)
        {
            return tree == P.tree;
        }
        return (tree == P.tree && *node_minus == *P.node_minus);
    }
    bool operator != (const PartialLevelOneTree & P) const
    {
        return !(*this == P);
    }

    bool IsPartialSubtree (const PartialLevelOneTree & P) const;

    // only apply to degree 1
    LevelOneTree Completion() const
    {
        auto u = tree;
        u.AddChildBelow(NodeMinusSequence());
        return u;
    }

    // only apply to degree 1
    SingleSequence CreateHangingNode() const
    {
        return Tree().CreateNodeFromUCF(NodeMinusSequence());
    }
};



class LevelTwoTree: public FuncTree < SingleSequence, PartialLevelOneTree>
{


private:

    //s is a node in the tree
    // add nodes below s whose domain forms a level-1 tree K
    void AddNodesBelowFromInput ( const string & name,
                                  LevelTwoTreeNode * const s,
                                  const LevelOneTree & K,
                                  const int & d)
    {


        LevelOneTree  P { Value(s).Completion()};

        vector<SingleSequence> pp;

        //      pp->emplace_back(nullptr);

        for (auto p = P.Root()->first_child; p != nullptr; p = P.NextEnumerate(p))
        {
            pp.emplace_back( P.EntireEntry(p));
        }

        for (auto e = K.SmallestNode(); e != K.Root(); e = e->BKRight())
        {
            cout<<endl<<EmptyString(d)<<"Possible values of the node component of "<<name<<" at "
                <<K.String(e)<<":"<<endl;

            for (unsigned long i = pp.size(); i!= 0; --i)
            {

                auto newnode = P.CreateNodeFromUCF(  pp [i-1]);

                cout<<EmptyString(d + indent)<< pp.size() - i + 1 << ". "
                    << ::String(newnode);
            }
            cout<<EmptyString(d + indent)<< pp.size() + 1 << ". "
                << "-1";
            cout<<endl<<EmptyString(d)<<"Which one? ";
            unsigned long k;
            cin >> k;
            while(k <= 0 || k > pp.size()+1)
            {
                cout<<EmptyString(d)<< "Error: Out of range! ";
                cin>>k;
            }
            if (k < pp.size()+1)
            {
                AddChildBelow(s,
                              K.EntireEntry(e),
                              PartialLevelOneTree (P,
                                                   pp[pp.size()-k]));
            }
            else
            {
                AddChildBelow(s, K.EntireEntry(e), PartialLevelOneTree(P));
            }

        }
    }


public:


    LevelTwoTree () = default;

    LevelTwoTree(const LevelTwoTree& Q) = default;

    LevelTwoTree(LevelTwoTree && f) :
        FuncTree<SingleSequence,PartialLevelOneTree>(std::move(f)){}


    LevelTwoTree& operator=(LevelTwoTree T)  {
        swap (*this, T);
        return *this;
    }


    ~LevelTwoTree() = default;



    string StringTree(const unsigned long interval, const unsigned long head) const;

    //the degree of the partial level <=1 tree Q(s)
    DEGREE Degree(const LevelTwoTreeNode * const s) const
    {
        return Value(s).Degree();
    }
    DEGREE Degree(const DoubleSequence & s) const
    {
        return Value(MyNodeInDomain(s)).Degree();
    }

    //the uniform cof of Q(s), i.e. the node-minus of Q(s)
    SingleSequence UCF(const DoubleSequence &s) const
    {
        return NodeMinusValue(s);
    }

    //input the tree
    void Input(const string name = "", const unsigned long d = 0)
    {


        LevelTwoTreeNode * current = Root();

        while (true)
        {
            string nodename = ::String(EntireEntryInDomain(current));


            LevelOneTree  K ;

            if (Degree(current) == DEGREE::ZERO)
            {
                cout<<EmptyString(d)<<nodename<<" has degree 0. It must be terminal"<<endl;
            }
            else
            {
                string level_1_tree_name = name+"{"+ nodename +"}";
                cout<<EmptyString(d)<<"Immediate successors of " <<name<<" at "
                    <<StringInDomain(current)
                    <<" forms a level-1 tree "<<level_1_tree_name  <<" :"<<endl;


                cout<<endl;
                K.Input(level_1_tree_name ,d + indent);
                cout<<endl;
            }

            if (K.IsTrivial())
            {
                if (current->IsEmpty())
                {
                    cout<<EmptyString(d)<<"Level-2 tree "<<name<<" input complete!"<<endl;
                    return;
                }
                while (current->IsLastBitRightMost())
                {
                    current = current->parent;
                    if (current->IsEmpty())
                    {
                        cout<<EmptyString(d)<<"Level-2 tree "<<name<<" input complete!"<<endl;
                        return;
                    }
                }
                current = current->right;
            }
            else
            {
                AddNodesBelowFromInput(name, current, K,d);
                current = current->first_child;
            }
        }
    }

    //  bool ContainsInDomainStar (const TreeNode* const s) const;

    //the tree component of Q(s)
    const LevelOneTree & TreeValue(const DoubleSequence & s) const
    {
        return Value(MyNodeInDomain(s)).Tree();
    }
    const LevelOneTree & TreeValue(const LevelTwoTreeNode * const s) const
    {
        return Value(s).Tree();
    }

    // the node minus value of Q(s)
    SingleSequence NodeMinusValue(const DoubleSequence & s) const
    {
        return Value(MyNodeInDomain(s)).NodeMinusSequence();
    }
    // the node minus value of Q(s)
    SingleSequence NodeMinusValue(const LevelTwoTreeNode * const s) const
    {
        return Value(s).NodeMinusSequence();
    }

    //the hanging node of Q(s)
    SingleSequence CreateHangingNode (const DoubleSequence & s) const
    {
        return Value(s).CreateHangingNode();
    }

    //the completion node of Q(s)
    LevelOneTree CreateCompletion (const DoubleSequence & s) const
    {
        return Value(s).Completion();
    }

};


bool IsBKPredecessor (const SingleSequence & s,
                      const SingleSequence & t,
                      const LevelOneTree & W)
{
    return (W.MyNode(s) == W.MyNode(t)->BKLeft());
}



class Level_leq_2_Tree
{

public:

    LevelOneTree tree_1;
    LevelTwoTree tree_2;

public:
    Level_leq_2_Tree() = default;

    ~Level_leq_2_Tree() = default;

    Level_leq_2_Tree(const Level_leq_2_Tree & Q) :
        tree_1 (Q.tree_1),
        tree_2 (Q.tree_2) {}

    Level_leq_2_Tree(const LevelOneTree & Q1, const LevelTwoTree & Q2) :
        tree_1(Q1),
        tree_2(Q2) {}

    Level_leq_2_Tree(Level_leq_2_Tree && Q) :
        tree_1 (LevelOneTree()),
        tree_2 (LevelTwoTree())
    {
        swap(*this,Q) ;
    }

    friend void swap (Level_leq_2_Tree & P, Level_leq_2_Tree & Q)
    {
        swap(P.tree_1,Q.tree_1);
        swap(P.tree_2,Q.tree_2);
    }

    Level_leq_2_Tree & operator = (Level_leq_2_Tree Q) {
        swap(*this,Q);
        return *this;
    }

    unsigned long Cardinality() const
    {
        return tree_1.Cardinality() + tree_2.Cardinality();
    }

    bool operator == (const Level_leq_2_Tree & Q) const
    {
        return (tree_1 == Q.tree_1 && tree_2 == Q.tree_2);
    }
    bool operator != (const Level_leq_2_Tree & Q) const
    {
        return !(*this == Q);
    }

    void Input (const string name = "", const unsigned long d = 0)
    {
        cout<<EmptyString(d)<<"Input the level <=2 tree "<<name<<endl<<endl;
        tree_1.Input(name + "1", d + indent);
        cout<<endl;
        tree_2.Input(name + "2", d + indent);
        cout<<endl;
        cout<<EmptyString(d)<<"Level <=2 tree "<<name<<" input complete!"<<endl;
    }
};





template <typename A>
class LevelTwoTreeBasedDesc
{

    friend LevelOneTreeNode* BaseUCF(const LevelTwoTreeBasedDesc &,
                                     const LevelOneTree &);

private:
    DEGREE degree;
    SingleSequence node_1;
    DoubleSequence node_2;
    // the discontinuous node
    //
    // having -1 case is
    // treated separately

    FuncTree<unsigned long,A> factor;
    // defalut if degree 1
    // we don't care anyway if degeree 1

    vector<FuncTreeNode<unsigned long,A>*> enumeration;
    // the enumeratin of the domain of factor according to the order by level-2 tree

    FuncTreeNode<unsigned long,A> * ucf_at_domain;
    // the node of ucf at domain of factor, or nullptr
    // if nullptr, must be indeed a node of a factor, not some synonym
    //

public:
    ~LevelTwoTreeBasedDesc() = default;

    LevelTwoTreeBasedDesc(LevelTwoTreeBasedDesc&& D)
    //    LevelTwoTreeBasedDesc()
        {
            swap(*this,D);
        }

    friend void swap(LevelTwoTreeBasedDesc & C,
                     LevelTwoTreeBasedDesc & D){
        std::swap(C.degree, D.degree);
        std::swap(C.node_1,D.node_1);
        std::swap(C.node_2,D.node_2);
        swap(C.factor,D.factor);
        std::swap(C.enumeration,D.enumeration);
        std::swap(C.ucf_at_domain,D.ucf_at_domain);
    }

    LevelTwoTreeBasedDesc& operator= (LevelTwoTreeBasedDesc D){
        swap(*this,D);
        return *this;
    }

    LevelTwoTreeBasedDesc():
        degree(DEGREE::TWO) ,
        node_1(SingleSequence()) ,
        node_2(DoubleSequence()),
        factor (FuncTree<unsigned long,A>())
    {
        enumeration = vector<FuncTreeNode<unsigned long,A>*> {factor.Root()};
        ucf_at_domain = factor.Root();
    }

    LevelTwoTreeBasedDesc(const LevelTwoTreeBasedDesc & D):
        degree (D.degree),
        node_1 (D.node_1),
        node_2 (D.node_2),
        factor (D.factor)
    {
        if (D.ucf_at_domain == nullptr)
        {
            ucf_at_domain = nullptr;
        }
        else
        {
            ucf_at_domain = factor.MyNode(D.ucf_at_domain);
        }
        for (auto && i : D.enumeration)
        {
            enumeration.emplace_back(factor.MyNode(i));
        }
    }

    LevelTwoTreeBasedDesc(const SingleSequence & n)   :
        //construct degree 1
        degree(DEGREE::ONE) ,
        node_1 (n),
        node_2 (DoubleSequence()),
        ucf_at_domain(nullptr)
    {}

    LevelTwoTreeBasedDesc(const DoubleSequence & n,
                          const FuncTree<unsigned long,A> & f,
                          const vector<SingleSequence> & e,
                          const SingleSequence & u) :
        //constructs degree 2, discontinuous type
        LevelTwoTreeBasedDesc(n,f,e)
    {
        ucf_at_domain = factor.MyNodeInDomain(u);
    }

    LevelTwoTreeBasedDesc(const DoubleSequence & n,
                          const FuncTree<unsigned long,A> & f,
                          const vector<SingleSequence> & e) :
        //constructs degree 2, continuous type
        degree(DEGREE::TWO),
        node_1 (SingleSequence()),
        node_2(n),
        factor(f),
        ucf_at_domain (nullptr)
    {
        for (auto && i : e)
        {
            enumeration.emplace_back(factor.MyNodeInDomain(i));
        }
    }


    DEGREE Degree() const
    {
        return degree;
    }
    const SingleSequence & GetNode_1() const
    {
        return node_1;
    }
    const DoubleSequence & GetNode_2() const
    {
        return node_2;
    }
    const FuncTree<unsigned long,A> & GetFactor() const
    {
        return factor;
    }


    bool IsConstant() const
    // is it constant?
    {
        return degree == DEGREE::TWO && node_2.empty() && ucf_at_domain != nullptr;
    }

    bool IsContinuousTypeAtDomain() const
    // is it continuous type?
    {
        if (degree == DEGREE::TWO)
        {
            if (factor.Cardinality() == node_2.size() + 2)
            {
                return true;
            }

        }
        return false;
    }

    bool IsDiscontinuousTypeAtDomain() const
    // is it discontinuous typE?
    {
        return !(IsContinuousTypeAtDomain());
    }


    FuncTreeNode<unsigned long,A> * UCFAtDomain() const
    {
        return ucf_at_domain;
    }

    FuncTreeNode<unsigned long,A> * LastNodeInDomain () const
    {
        return enumeration.back();
    }

    bool operator == (const LevelTwoTreeBasedDesc & D) const
    {
        if (degree != D.degree)
        {
            return false;
        }
        if (degree == DEGREE::ONE)
        {
            return (node_1 == D.node_1);
        }
        if (node_2 != D.node_2)
        {
            return false;
        }
        if (factor != D.factor)
        {
            return false;
        }
        return true;
    }
    // only compare desc of the same trees (Q,W) in applications,
    // so enough to compaer the node and the factoring map

    bool operator != (const LevelTwoTreeBasedDesc & D) const
    {
        return !(*this == D);
    }

    bool operator < (const LevelTwoTreeBasedDesc& D) const
    {
        if (degree == DEGREE::ONE && D.degree == DEGREE::TWO)
        {
            return true;
        }
        if (degree == DEGREE::TWO && D.degree == DEGREE::ONE)
        {
            return false;
        }
        if (degree == DEGREE::ONE)
        {
            return node_1 < D.node_1;
        }
        return Representation() < D.Representation();
    }

    bool operator <= (const LevelTwoTreeBasedDesc& D) const
    {
        return *this < D || *this == D;
    }
    bool operator > (const LevelTwoTreeBasedDesc& D) const
    {
        return !(*this <= D);
    }
    bool operator >= (const LevelTwoTreeBasedDesc& D) const
    {
        return !(*this < D);
    }


    vector<tuple<int,SingleSequence,A>> Representation() const
    {
        vector<tuple<int,SingleSequence,A>> out;
        if (degree == DEGREE::ONE)
        {
            cout<<"you are trying to represent a level-21 desc of deg 1!"<<endl;
            return out;
        }

        auto e = node_2.cbegin();

        for (auto && i = enumeration.cbegin() + 1; i != enumeration.cend(); ++i)
        {
            out.emplace_back( tuple<int,SingleSequence,A> {2, SingleSequence(),(*i)->Entry().second});
            if (e != node_2.cend())
            {
                out.emplace_back(tuple<int,SingleSequence,A> {1,*e, A()});
                ++e;
            }
            else
            {
                out.emplace_back(tuple<int,SingleSequence,A> {-1, SingleSequence(), A()});
                break;
            }
        }
        return out;
    }


    string String(const unsigned long d=0) const
    {
        //formats it into a string
        string s = EmptyString(d) + "degree: " ;
        if (degree == DEGREE::ONE)
        {
            s += "1\n";
            s += EmptyString(d) + "node: " + ::String(node_1) + "\n";
        }
        else
        {
            s += "2\n";
            s += EmptyString(d) + "node: " + ::String(node_2);
            if (node_2.empty())
            {
                if (IsContinuousTypeAtDomain())
                {
                    s.pop_back();
                    s.pop_back();
                    s += "-1";
                }
            }
            else if (IsContinuousTypeAtDomain())
            {
                s += " -1";
            }
            s += "\n";
        }
        if (degree == DEGREE::TWO)
        {
            s+= EmptyString(d) + "factor map:\n";
            for (auto &&  p = factor.Root(); p != nullptr; p = factor.NextEnumerate(p))
            {

                string factor_string = ::String( factor.EntireEntryInDomain(p));
                factor_string += "|-->";
                factor_string += ::String(factor.Value(p));
                s += EmptyString(d + indent) + factor_string + "\n";
            }
 //           s+= "Representation: "+ ::String(Representation()) + "\n";

        }

        return s;
    }

    string String221(const unsigned long d=0) const
    {
        //formats it into a string
        string s = EmptyString(d) + "degree: " ;
        if (degree == DEGREE::ONE)
        {
            s += "1\n";
            s += EmptyString(d) + "node: " + ::String(node_1) + "\n";
        }
        else
        {
            s += "2\n";
            s += EmptyString(d) + "node: " + ::String(node_2);
            if (node_2.empty())
            {
                if (IsContinuousTypeAtDomain())
                {
                    s.pop_back();
                    s.pop_back();
                    s += "-1";
                }
            }
            else if (IsContinuousTypeAtDomain())
            {
                s += " -1";
            }
            s += "\n";
        }
        if (degree == DEGREE::TWO)
        {
            s+= EmptyString(d) + "factor map:\n";
            for (auto &&  p = factor.Root(); p != nullptr; p = factor.NextEnumerate(p))
            {

                string factor_string = ::String( factor.EntireEntryInDomain(p));
                factor_string += "|--> the following level-21 desc:\n" ;
                factor_string += factor.Value(p).String(d+indent);
                s += EmptyString(d + indent) + factor_string + "\n";
            }
 //           s+= "Representation: "+ ::String(Representation()) + "\n";

        }

        return s;
    }

    void DiscontinuousTrim()
    {
        // if the node in the level-2 tree ends with -1
        //
        // remove the last node of factor and the -1

        if (IsContinuousTypeAtDomain())
        {
            enumeration.pop_back();
            ucf_at_domain = factor.Remove(ucf_at_domain);
        }
    }

    void Extend(const SingleSequence & extend_node,
                const A & new_in_image,
                const SingleSequence & new_ucf)
    {
        // extend the current degree-2 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is not -1
        //

        Extend(extend_node, new_in_image);

        ucf_at_domain = factor.MyNodeInDomain(new_ucf);
    }
    void Extend(const SingleSequence & extend_node,
                const A & new_in_image)
    {
        // extend the current degree-21 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is -1
        //
        node_2.emplace_back (extend_node);

        auto new_in_domain = AddChildBelow<A>(factor,
                                              ucf_at_domain,
                                              new_in_image);

        enumeration.emplace_back( new_in_domain );
        ucf_at_domain = nullptr;
    }

    void Extend(const A & new_in_image)
    {
        // extend the current degree-2 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new continuous desc
        //

        auto new_in_domain = AddChildBelow<A>(factor,
                                              ucf_at_domain,
                                              new_in_image);

        enumeration.emplace_back( new_in_domain );

        ucf_at_domain = new_in_domain;
    }


    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node,
                              const SingleSequence & new_ucf)
    {
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is not -1

        node_2.back() = last_entry_in_node;

        ucf_at_domain = factor.MyNodeInDomain(new_ucf);
    }

    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node)
    {
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is -1

        node_2.back() = last_entry_in_node;

        ucf_at_domain = nullptr;
    }

    void MoveLastEntryInNode ()
    {
        //current is disc type
        // move the last entry to -1.

        node_2.pop_back();
        ucf_at_domain = LastNodeInDomain();

    }


    //****************//
    // specific to 21 desc!!!//

    SingleSequence UCF() const
    //uniform cofinality, provided not -1
    {
        return factor.Value(ucf_at_domain);
    }

    bool IsContinuousType_Star(const LevelOneTree & W) const
    // is it *-W-continuous type>
    {
        if (degree == DEGREE::ONE)
            return false;

        if (ucf_at_domain == nullptr)
        {
            return true;
        }

        auto ucf = UCF();

        if ( W.IsTrivial() ||  ucf ==  W.SmallestEntry())
        {
            return true;
        }

        if ( ucf_at_domain->BKLeft() == nullptr )
        {
            return false;
        }

        if (IsBKPredecessor(factor.Value(ucf_at_domain->BKLeft()), factor.Value(ucf_at_domain), W))
        {
            return true;
        }
        return false;
    }


    bool IsDiscontinuousType_Star(const LevelOneTree & W) const
    // is it *-W-disc type?>
    {
        return !(IsContinuousType_Star(W));
    }

    // ************finished specifec to 21-desc**************//

    //**************************

    //************starting specific to 221-desc******************//


    A UCF_As21Desc() const
    //uniform cofinality, regarded as a (*, Q \otimes W) desc, provided not -1
    {
        return factor.Value(ucf_at_domain);
    }


    bool IsContinuousType_Star_As21Desc (const Level_leq_2_Tree & Q,
                                         const LevelOneTree & W) const
    {
        // is it *-continuous type as a (*, Q\otimes W)--desc?

        if (degree == DEGREE::ONE)
            return false;
        if (ucf_at_domain == nullptr)
        {
            return true;
        }
        auto ucf_21_desc = make_shared<A>( UCF_As21Desc() );

        auto ucf_21_desc_left = BKLeft(ucf_21_desc, Q, W);

        if ( ucf_21_desc_left == nullptr )
        {
            return true;
        }

        if ( ucf_at_domain->BKLeft() == nullptr )
        {
            return false;
        }

        auto ucf_21_desc_to_compare = factor.Value(ucf_at_domain->BKLeft());

        if ( *ucf_21_desc_left == ucf_21_desc_to_compare)
        {
            return true;
        }
        return false;

    }
    bool IsDiscontinuousType_Star_As21Desc (const Level_leq_2_Tree & Q,
                                            const LevelOneTree & W) const
    {
        return !(IsContinuousType_Star_As21Desc(Q,W));
    }

};


string String(const Level_21_Desc & D) {
return D.String();
}





// provided these nodes are alraedy in the tree or domain of tree!!
LevelOneTreeNode* BKLeft(const SingleSequence & s, const LevelOneTree & W)
{
    return W.MyNode(s)->BKLeft();
}

LevelTwoTreeNode* BKLeft(const DoubleSequence & s, const LevelTwoTree & W)
{
    return W.MyNodeInDomain(s)->BKLeft();
}

/*
LevelTwoTreeNode* Left(const DoubleSequence & s, const LevelTwoTree & W)
{
    return W.MyNodeInDomain(s)->Left();
}*/


shared_ptr<Level_21_Desc> BKLeft(const shared_ptr<Level_21_Desc> & D,
                                 const Level_leq_2_Tree & Q,
                                 const LevelOneTree & W)
{
    auto Q1 = Q.tree_1;
    auto Q2 = Q.tree_2;

    // deal with the degree 1 case first
    //
    if (D->Degree() == DEGREE::ONE)
    {
        auto  left = BKLeft(D->GetNode_1(), Q1);
        if ( left != nullptr)
        {
            return make_shared<Level_21_Desc>( Q1.EntireEntry(left));
        }
        return nullptr;
    }

    // now D degree 2
    //
    auto node = Q2.MyNodeInDomain(D->GetNode_2());

    shared_ptr<Level_21_Desc> output = make_shared<Level_21_Desc> (*D);

    output->DiscontinuousTrim();

    //now output is the desc to move, in either case

    if (D->IsDiscontinuousType_Star(W))
    {
        //end extend output

        auto ucf = D->UCF();
        auto new_in_image = BKLeft(ucf, W);
        // the biggest element before ucf of D
        // it must be put on the next entry


        if (node->IsTerminal())
        {
            // nothing in Q2 extending
            // use -1
            output->Extend(W.EntireEntry(new_in_image));
        }
        else
        {
            // find the bigest extension
            auto extend_node_in_Q2 = node->LastChild();

            //fint the last entry
            SingleSequence  extend_node (Q2.LastEntryInDomain(extend_node_in_Q2));

            if (Q2.Degree(extend_node_in_Q2) == DEGREE::ZERO)
            {
                // if the biggest extension of degree 0
                output->Extend(extend_node, W.EntireEntry(new_in_image));
            }
            else
            {
                // if the biggest extension of degree 1
                auto new_ucf = Q2.NodeMinusValue(extend_node_in_Q2);
                // find the ucf, extend it
                output->Extend(extend_node, W.EntireEntry(new_in_image), new_ucf);

            }

        }
        return output;

    }
    else
    {
        //cannot extend D
        if (D->IsConstant())
        {
            // D constant , so W must be trivial
            if (Q1.IsNonTrivial())
            {
                //if Q1 trivial, the greatest of Q1 is the left
                return make_shared<Level_21_Desc>(Level_21_Desc(Q1.EntireEntry(Q1.Root()->BKLeft())));
            }
            else
            {
                // if Q1 is also trivial, no more
                return nullptr;
            }
        }
        else if (output->IsConstant())
        {
            //if D- is constant,
            // D must be (-1,min(W))
            if (Q1.IsNonTrivial())
            {
                // Q1 is non trivial
                // assign the biggest
                return make_shared<Level_21_Desc>(Level_21_Desc(Q1.EntireEntry(Q1.Root()->BKLeft())));
            }
            else
            {
                // Q1 is trivial, no more
                return nullptr;
            }
        }
        else
        {
            // move the last bit in Q2

            if (node->Left() == nullptr)
            {
                //left mot movable
                // must move to -1
                output->MoveLastEntryInNode();
            }
            else
            {
                // find the left
                auto left = node->Left();
                auto last_entry_in_node = Q2.LastEntryInDomain(left);

                //
                if (Q2.Degree(left) == DEGREE::ZERO)
                {
                    // if the left of degree 0
                    output->MoveLastEntryInNode(last_entry_in_node);
                    // move it
                }
                else
                {
                    // if the left of degree 1
                    //find the new ucf
                    auto new_ucf = Q2.NodeMinusValue(left);
                    output->MoveLastEntryInNode(last_entry_in_node, new_ucf);
                }
            }
            return output;
        }
    }
}



// given D, a (Q,W)-desc
// D' , either nullptr or a (Q,W')-desc whose restriction to (Q,W) is D,
// produce the left of D' whose restriction is still D but D' not D
// W' is the completion of (W,w+), w+ is the hanging node whose ucf in W is w
//
shared_ptr<Level_21_Desc> Left(const shared_ptr<Level_21_Desc> & D,
                               const shared_ptr<Level_21_Desc> & D_prime,
                               const Level_leq_2_Tree & Q,
                               const LevelOneTree & W,
                               const LevelOneTree & W_prime,
                               const LevelOneTreeNode * w)
{
    auto ucf_at_domain = D->UCFAtDomain();
    auto sigma = D->GetFactor();
    if (ucf_at_domain == nullptr)
    {
        return nullptr;
    }
    if (sigma.Value(ucf_at_domain) != W_prime.EntireEntry(w->Parent()))
    {
        return nullptr;
    }
    // ucf of D must be non -1, and equal to w, to be able to extend

    if (D_prime  == nullptr)
    {
        return BKLeft(D, Q, W_prime);
    }
    // the first on the left of D is the (Q,W')-left

    auto output = BKLeft(D_prime, Q, W_prime);
    auto compared = BKLeft(D, Q, W);
    if (output == nullptr)
    {
        return nullptr;
    }
    if ( compared == nullptr)
    {
        return output;
    }
    if ( *output == *compared)
    {
        return nullptr;
    }
    return output;
}

typedef FuncTreeNode<unsigned long, Level_21_Desc> Level_121_FactorNode;
typedef FuncTree<unsigned long, Level_21_Desc> Level_121_Factor;

Level_121_Factor TensorProduct(const Level_leq_2_Tree & Q, const LevelOneTree & W)
{

    Level_121_Factor output;

    shared_ptr<Level_21_Desc> D = make_shared<Level_21_Desc> (Level_21_Desc()); //initialize to the constant desc

    D = BKLeft(D,Q,W);

    auto current = output.Root();

    while ( D != nullptr )
    {
        current = output.AddChildBelow(current, current->NumberOfChildren() , *D);
        D = BKLeft(D,Q,W);
    }

    return output;

}



//given C , a (T,Q,W)-desc
//given C', either nullptr or a (T,Q,W')-desc whose restriction to (T,Q,W) is C
// where W' is a one-node extension of W whose ucf is w,
// outputs the candidate of the left of C' whose restriction to (T,Q,W) is still C
//
// ****** candidate means: good at transition point***********
//
shared_ptr<Level_221_Desc> LeftCandidate(const Level_221_Desc & C,
        const shared_ptr<Level_221_Desc> & C_prime,
        const Level_leq_2_Tree &           T,
        const Level_leq_2_Tree &           Q,
        const LevelOneTree &               W,
        const LevelOneTree &               W_prime,
        const LevelOneTreeNode *             w)
{

    auto T2 = T.tree_2;



    if (C_prime == nullptr)
    {

        shared_ptr<Level_221_Desc> output = make_shared<Level_221_Desc> (C);

        output->DiscontinuousTrim();
        // define a shared pointer to output

        //create a valid candidate desc, well-behaved at transition point

        auto critical_node = C.UCFAtDomain();
        auto factor = C.GetFactor();
        auto critical_21_desc = make_shared<Level_21_Desc> (factor.Value(critical_node));
        // the desc to be decreased

        auto node_in_T2 = T2.MyNodeInDomain(C.GetNode_2());


        auto critical_left = Left(critical_21_desc, nullptr, Q, W, W_prime, w);
        //the next smaller desc

        if (critical_left == nullptr)
        {
            return nullptr;
        }

        //starting to extend
        if (node_in_T2->IsTerminal())
        {
            // nothing in T2 extending
            // use -1
            output->Extend(*critical_left);
        }
        else
        {
            //find the biggest extension
            auto extend_node_in_T2 = node_in_T2->BKLeft();

            //find the last entry
            SingleSequence extend_node (T2.LastEntryInDomain(extend_node_in_T2));

            if (T2.Degree(extend_node_in_T2) == DEGREE::ZERO)
            {
                // if the biggest extension of degree 0
                output->Extend(extend_node, *critical_left);
            }
            else
            {
                // if the biggest extension of degree 1
                auto new_ucf = T2.NodeMinusValue(extend_node_in_T2);
                // find the ucf, extend it
                output->Extend(extend_node, *critical_left, new_ucf);
            }
        }
        return output;
    }


    // now C'is not nullptr. it is a potential extension, validated at transition point

    shared_ptr<Level_221_Desc> output = make_shared<Level_221_Desc> (*C_prime);

    output->DiscontinuousTrim();
    // define a shared pointer to output
    // copy C' first

    auto node_in_T2 = T2.MyNodeInDomain(C_prime->GetNode_2());

    auto effective_length = T2.Length(node_in_T2);

    // later check if it properly extend the core part of C
    auto node_in_T2_to_compare = T2.MyNodeInDomain(C.GetNode_2());
    auto effective_length_to_compare = T2.Length(node_in_T2_to_compare);

    if (C_prime->IsDiscontinuousType_Star_As21Desc(Q,W_prime))
    {
        //C'_effective part can be end extended as (Q,W')-desc

        auto critical_21_desc =
            make_shared<Level_21_Desc>
            (C_prime->UCF_As21Desc());


        shared_ptr<Level_21_Desc> critical_left;

        if (effective_length > effective_length_to_compare)
        {
            critical_left = BKLeft(critical_21_desc, Q, W_prime);
            //no problem extending
        }
        else
        {
            // this means C' is C_effective_part extended by
            //  (D,-1), where D is the transitioning 21_Desc
            // so C'_effective_part = C_effective_part
            //
            // need to find another D'<D, good transitioning extension
            //
            auto bound_in_C = make_shared<Level_21_Desc> (C.UCF_As21Desc());
            critical_left = Left(bound_in_C, critical_21_desc, Q, W, W_prime, w);
            if (critical_left == nullptr)
            {
                //squeezed out
                // no more
                return nullptr;
            }
            //found the good transition
        }

        // now critical_left is the extention of C'_effective part,
        // need to find the node


        if (node_in_T2->IsTerminal())
        {
            // not extendable in T2
            // use -1
            output->Extend(*critical_left);
        }
        else
        {
            //find the biggest extension
            auto extend_node_in_T2 = node_in_T2->BKLeft();

            // find the last entry
            SingleSequence extend_node (T2.LastEntryInDomain(extend_node_in_T2));

            if (T2.Degree(extend_node_in_T2) == DEGREE::ZERO)
            {
                // if the biggest extension of degree 0
                output->Extend(extend_node, *critical_left);
            }
            else
            {
                //if the beggest extension of degree 1
                auto new_ucf = T2.NodeMinusValue(extend_node_in_T2);
                // find the ucf, extend it
                output->Extend(extend_node, *critical_left, new_ucf);
            }
        }

    }
    else
    {
        //cannot extend C_effective_part

        if (effective_length == effective_length_to_compare )
        {
            // C' is C_effective_part exteded by (D,-1), D not extendable
            return nullptr;
            // get squeezed out
        }

        //otherwise,
        // if node_in_T2 is the root, get sqeezed out
        // if not, move to the left

        if (node_in_T2->IsEmpty())
        {
            // it is (least desc, -1)
           return nullptr;
            // squezed out
        }

        //start moving

        if (node_in_T2->Left() == nullptr)
        {
            // no left
            // move to -1
            output->MoveLastEntryInNode();
        }
        else
        {
            //find the left
            auto left = node_in_T2->Left();
            auto last_entry_in_node = T2.LastEntryInDomain(left);

            //
            if (T2.Degree(left) == DEGREE::ZERO)
            {
                // if the left of degree 0
                output->MoveLastEntryInNode(last_entry_in_node);
                //move it
            }
            else
            {
                //if the left of degree 1
                // find the new ucf
                auto new_ucf = T2.NodeMinusValue(left);
                output->MoveLastEntryInNode(last_entry_in_node, new_ucf);
            }
        }
    }
    return output;
}



//given C, a (T,Q,W)-desc whose ucf at W is w,
// W' is the completion of (W,w+), w is the ucf of (W,W+)
// C' is a candidate (T,Q,W')-desc, produced by the LeftCandidate function, good at transition
//verify if C' is a (T,Q,W')-desc
//
bool Validate (const Level_221_Desc &     C,
               const shared_ptr<Level_221_Desc> &     C_prime,
               const Level_leq_2_Tree &  T,
               const Level_leq_2_Tree &  Q,
               const LevelOneTree &      W,
               const LevelOneTree &      W_prime,
               const LevelOneTreeNode*       w)
{

    if (C_prime == nullptr)
    {
        return false;
    }

    auto T2 = T.tree_2;

    auto node_in_T2 = T2.MyNodeInDomain(C_prime->GetNode_2());

    if (C_prime->IsDiscontinuousTypeAtDomain())
    {
        return true;
    }

    auto effective_length = T2.Length(node_in_T2);

    auto effective_node_to_compare = T2.MyNodeInDomain(C.GetNode_2());
    auto effective_length_to_compare = T2.Length(effective_node_to_compare);

    if (effective_length > effective_length_to_compare)
    {
        return true;
    }

    //now C' is C_effective_part plus (D, -1)
    // we need to make sure of the well-behavior of D

    //if last value is not w, then w must have shown before
    auto last_node_in_C_prime = C_prime->LastNodeInDomain();
    auto critical_desc = C_prime->GetFactor().Value(last_node_in_C_prime);
    auto critical_factor = critical_desc.GetFactor();

    auto last_node = critical_desc.LastNodeInDomain();
    auto last_value = critical_factor.Value(last_node);
    if (last_value != W_prime.EntireEntry(w))
    {
        return true;
    }

    //otherwise, last value is w
    //then critical_desc must discontinuous
    return critical_desc.IsDiscontinuousTypeAtDomain();

}



//given C , a (T,Q,W)-desc
//given C', either nullptr or a (T,Q,W')-desc whose restriction to (T,Q,W) is C
// where W' is a one-node extension of W whose ucf is w,
// outputs the left of C' whose restriction to (T,Q,W) is still C
//
shared_ptr<Level_221_Desc> Left (const Level_221_Desc &     C,
                                 const shared_ptr<Level_221_Desc> &     C_prime,
                                 const Level_leq_2_Tree &  T,
                                 const Level_leq_2_Tree &  Q,
                                 const LevelOneTree &      W,
                                 const LevelOneTree &      W_prime,
                                 const LevelOneTreeNode*       w)
{


    if (C_prime != nullptr)
    {

        //search by candidate  and verify them

        auto current = make_shared<Level_221_Desc> (*C_prime);

        do
        {
            current = LeftCandidate(C, current, T, Q, W, W_prime, w);
            //move left

            if (current == nullptr)
            {
                return nullptr;
            }
            //hit the wall. no more

            if (Validate(C, current, T, Q, W, W_prime, w))
            {
                return current;
                //validated, retun the current desc
            }
            // if not validated, continue searching
        }
        while (true);
    }

    auto current = LeftCandidate(C, nullptr, T,Q,W,W_prime,w);

    do
    {


        if (current == nullptr)
        {
            return nullptr;
        }
        //hit the wall. no more

        if (Validate(C, current, T, Q, W, W_prime, w))
        {
            return current;
            //validated, retun the current desc
        }
        // if not validated, continue searching

        current = LeftCandidate(C, current, T, Q, W, W_prime, w);
        //move left

    }
    while (true);


}

// C is a (*,*,W)-desc
// get the w such that C is a (*,*,(W,-1))-desc or (*,*,(W,w+))-desc,
// w is the ucf of the base
//
LevelOneTreeNode * BaseUCF (const Level_221_Desc & C, const LevelOneTree & W)
{

    if (C.ucf_at_domain == nullptr)
    {
        return nullptr;
    }

    auto critical_desc = C.UCF_As21Desc();

    if (critical_desc.ucf_at_domain == nullptr)
    {
        return nullptr;
    }

    auto critical_desc_ucf = critical_desc.UCF_As21Desc();

    return W.MyNode(critical_desc_ucf);
}





class Level_222_Factor
{

public:

    Level_leq_2_Tree domain;
    Level_121_Factor factor_1;
    FuncTree<SingleSequence,Level_221_Desc> factor_2;


public:

    Level_222_Factor() = default;
    Level_222_Factor(const Level_222_Factor & pi) = default;
//   Level_222_Factor(const LevelOneFactor & pi1, const LevelTwoFactor & pi2);


    unsigned long Cardinality()
    {
        return factor_1.Cardinality() + factor_2.Cardinality();
    }

    bool operator == (const Level_222_Factor & pi) const
    {
        return (domain == pi.domain && factor_1 == pi.factor_1 && factor_2 == pi.factor_2);
    }
    bool operator != (const Level_222_Factor & pi) const
    {
        return !(*this == pi);
    }

    Level_leq_2_Tree &   Domain()
    {
        return domain;
    }
    Level_121_Factor &   Factor_1()
    {
        return factor_1;
    }
    FuncTree<SingleSequence,Level_221_Desc>  &  Factor_2()
    {
        return factor_2;
    }


    // n is a node is the (X,T,Q)-factor map
    // the 221-desc in n is a (T,Q,W)-Desc
    // create one-node-in-W extensions of W,
    // and put them under n
    //
    // move both pointers to last children
    // if not , move to nullptr
    //
    void
    CreateChildren(
        LevelTwoTreeNode * & n_tree,
        FuncTreeNode<SingleSequence,Level_221_Desc> * & n_factor,
        const Level_leq_2_Tree &    T,
        const Level_leq_2_Tree &    Q)
    {

        auto temp_factor = n_factor;
        auto temp_tree = n_tree;

        auto C = factor_2.Value(n_factor);
        // the 221-desc in n

        auto & X = domain;
        auto & X2 = X.tree_2;

        auto W = X2.Value(n_tree).Tree();
        auto w_node = X2.Value(n_tree).NodeMinusInTree();

        if (w_node == nullptr)
        {
            // the node in X is degree 0,
            // impossible to extend
            //
            n_tree = nullptr;
            n_factor = nullptr;
            return;
        }

        auto w_entry = W.EntireEntry(w_node);

        auto W_prime = X2.Value(n_tree).Completion();
        // W' is the completion of X2(x)

        auto w = W_prime.MyNode(w_entry)->LastChild();

        auto prev_desc = Left(C, nullptr, T, Q, W, W_prime, w);
        // try to build a child

        if (prev_desc == nullptr)
        {
            // if unsuccessful, no child
            n_tree = nullptr;
            n_factor = nullptr;
            return;
        }

        // found the child, add it into both X2 and factor_2 according to
        // the new ucf

        // add into factor2

        auto current_in_factor = AddChildBelow<Level_221_Desc>
                                 ( factor_2, n_factor, *prev_desc );


        // starting to add into X2
        LevelOneTreeNode * new_ucf = BaseUCF(*prev_desc, W_prime) ;
        LevelTwoTreeNode * current_in_X2;
        if ( new_ucf == nullptr)
        {
            // the new node in X2 is degree 0
            current_in_X2 = AddChildBelow<PartialLevelOneTree>
                            (X2, n_tree, PartialLevelOneTree(W_prime) );
        }
        else
        {
            auto new_ucf_entry = W_prime.EntireEntry(new_ucf);
            // the new node in X2 is degree 1
            current_in_X2 = AddChildBelow<PartialLevelOneTree>
                            ( X2, n_tree, PartialLevelOneTree(W_prime, new_ucf_entry));
        }

        // find new children, add to the left
        do
        {
            prev_desc = Left(C, prev_desc, T, Q, W, W_prime, w);
            if (prev_desc == nullptr)
            {
                //reached the end, break,
                break;
            }
            // add into factor2
            current_in_factor = AddSiblingLeft<Level_221_Desc>
                                ( factor_2, current_in_factor, *prev_desc );

            // starting to add into X2
            new_ucf = BaseUCF(*prev_desc, W_prime) ;
            if ( new_ucf == nullptr)
            {
                // the new node in X2 is degree 0
                current_in_X2 = AddSiblingLeft<PartialLevelOneTree>
                                (X2, current_in_X2, PartialLevelOneTree(W_prime) );
            }
            else
            {
                auto new_ucf_entry = W_prime.EntireEntry(new_ucf);

                // the new node in X2 is degree 1
                current_in_X2 = AddSiblingLeft<PartialLevelOneTree>
                                ( X2, current_in_X2, PartialLevelOneTree(W_prime, new_ucf_entry));

            }
        }
        while(true);

        n_factor = temp_factor->LastChild();
        n_tree = temp_tree->LastChild();

        return;
    }
};



Level_222_Factor TensorProduct(const Level_leq_2_Tree & T, const Level_leq_2_Tree & Q)
{
    Level_222_Factor pi;
    pi.factor_1 = TensorProduct(T, Q.tree_1);
    pi.domain.tree_1 = pi.factor_1.Domain();

    // the level_1 component is just 21 tensor product


    auto current_factor = pi.factor_2.Root();
    auto current_tree = pi.domain.tree_2.Root();


    auto temp_factor = current_factor;
    auto temp_tree = current_tree;



    while(true)
    {

        pi.CreateChildren(temp_tree,temp_factor,T,Q);


        if (temp_factor != nullptr)

        {
            current_factor = temp_factor;
            current_tree = temp_tree;
            continue;
        }


        while (current_factor != nullptr &&
                current_factor->Left() == nullptr)
        {
            current_factor = current_factor->Parent();
            current_tree = current_tree->Parent();
        }
        if (current_factor == nullptr)
        {
            return pi;
        }
        current_factor = current_factor->Left();
        current_tree = current_tree->Left();

        temp_factor = current_factor;
        temp_tree = current_tree;

    }
}


string String (const vector<tuple<int,SingleSequence,Level_21_Desc>> & r)
{
    string output;
    for (auto && i : r)
    {
        if (std::get<0> (i) == 2)
        {
            output += String(std::get<2> (i));
        }
        else if (std::get<0>(i) == 1){
            output += String(std::get<1> (i));
        }
        else
        {
            output += "-1";
        }
    }
    return output;
}



#endif // SHARP_H_INCLUDED
