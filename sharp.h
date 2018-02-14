#ifndef SHARP_H_INCLUDED
#define SHARP_H_INCLUDED

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::string;
//using std::shared_ptr;
//using std::unique_ptr;
using std::vector;
using std::to_string;
//using std::make_shared;
using std::tuple;
using std::make_tuple;
using std::ofstream;

constexpr unsigned indent = 2;
constexpr unsigned interval = 7;

string EmptyString (unsigned long d);


enum class DEGREE
{
    ZERO, ONE, TWO
};

enum class DIRECTION
{
    NA, DOWN, LEFT
};

enum class STATE
{
    VALID, INVALID
};

string to_string (const DIRECTION & d)
{
    if (d == DIRECTION::NA)
    {
        return "NA";
    }
    if (d == DIRECTION::DOWN)
    {
        return "DOWN";
    }
    return "LEFT";
}
string to_string (const DEGREE & d)
{
    if (d == DEGREE::ONE)
    {
        return "ONE";
    }
    if (d == DEGREE::TWO)
    {
        return "TWO";
    }
    return "ZERO";
}

template <typename TYPE>
class TreeNode;
template <typename TYPE>
class Tree;


template<typename ENTRYTYPE, typename VALUETYPE>
using FuncTreeNode = TreeNode<pair<ENTRYTYPE, VALUETYPE>>;
template <typename ENTRYTYPE, typename VALUETYPE>
class FuncTree;

typedef vector<unsigned long>
SingleSequence;
typedef vector<SingleSequence>
DoubleSequence;

typedef tuple<DEGREE, SingleSequence, DoubleSequence>
leq_2_Sequence;

typedef TreeNode<unsigned long>
LevelOneTreeNode;
class LevelOneTree;

class PartialLevelOneTree;

typedef FuncTreeNode<unsigned long, SingleSequence>
LevelOneFactorNode;
typedef FuncTree<unsigned long, SingleSequence>
LevelOneFactor;


typedef FuncTreeNode <SingleSequence, PartialLevelOneTree>
LevelTwoTreeNode;
class LevelTwoTree;


typedef tuple<DEGREE, LevelOneTreeNode *, LevelTwoTreeNode * >
Level_leq_2_TreeNode;

class PartialLevel_leq_2_Tree;

template <typename A>
class LevelTwoTreeBasedDesc;

typedef LevelTwoTreeBasedDesc<SingleSequence>
Level_21_Desc;

typedef FuncTreeNode<unsigned long, Level_21_Desc>
Level_121_FactorNode;

typedef FuncTree<unsigned long, Level_21_Desc>
Level_121_Factor;


typedef LevelTwoTreeBasedDesc<Level_21_Desc>
Level_221_Desc;

typedef tuple <   DEGREE,
        LevelOneTreeNode*,
        Level_121_FactorNode*,
        LevelTwoTreeNode*,
        FuncTreeNode<SingleSequence, Level_221_Desc> *
        >
        Level_222_FactorNode;

class Level_222_Factor;

DEGREE Degree (const Level_222_FactorNode &);
LevelOneTreeNode* NodeInTree_1 (const Level_222_FactorNode &);
LevelTwoTreeNode* NodeInTree_2 (const Level_222_FactorNode &);
Level_121_FactorNode* NodeInFactor_1 (const Level_222_FactorNode &);
FuncTreeNode<SingleSequence, Level_221_Desc>* NodeInFactor_2 (const Level_222_FactorNode &);


typedef FuncTreeNode <SingleSequence, PartialLevel_leq_2_Tree>
LevelThreeTreeNode;

typedef pair<LevelOneTree, LevelOneTreeNode * >
FinalTreeWithNode;

class Level_322_Desc;

Level_leq_2_TreeNode
zeroLevel_leq_2_TreeNode = Level_leq_2_TreeNode
{
    DEGREE::ZERO,
    nullptr,
    nullptr,
};

leq_2_Sequence
zero_leq_2_Sequence = leq_2_Sequence
{
    DEGREE::ZERO,
    SingleSequence(),
    DoubleSequence(),
};

class Level_leq_2_Tree;

Level_222_FactorNode
zeroLevel_leq_2_FactorNode = Level_222_FactorNode
{
    DEGREE::ZERO,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};

class LevelThreeTree;

typedef pair<LevelThreeTreeNode*, FuncTreeNode<SingleSequence, Level_322_Desc>*>
Level_332_FactorNode;

Level_332_FactorNode zeroLevel_332_FactorNode = Level_332_FactorNode (nullptr, nullptr);

class Level_332_Factor;

string to_string (const Level_21_Desc & D,
                  const unsigned & d = 0);

string to_string (const leq_2_Sequence & s);

string to_string (const Level_221_Desc & C,
                  const unsigned & d = 0);
string to_string (const Level_322_Desc & B,
                  const unsigned & d = 0);


string to_string (const LevelOneTree & Q,
                  const unsigned & d = 0);
string to_string (const Level_leq_2_Tree & Q,
                  const unsigned & d = 0);
string to_string (const LevelTwoTree & Q,
                  const unsigned & d = 0);
string to_string (const PartialLevel_leq_2_Tree & Q,
                  const unsigned & d = 0);
string to_string (const LevelThreeTree & Q,
                  const unsigned & d = 0);
string to_string (const Level_332_Factor & Q,
                  const unsigned & d = 0);
string to_string (const Level_222_Factor & Q,
                  const unsigned & d = 0);

//
//template <typename T>
//bool operator == (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator <= (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator >= (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator < (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator > (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator != (const shared_ptr<T> & a, const  shared_ptr<T> & b) = delete;
//template <typename T>
//bool operator == (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
//template <typename T>
//bool operator <= (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
//template <typename T>
//bool operator >= (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
//template <typename T>
//bool operator < (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
//template <typename T>
//bool operator > (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;
//template <typename T>
//bool operator != (const unique_ptr<T> & a, const  unique_ptr<T> & b) = delete;


//define the BK order
template <typename TYPE>
bool operator < (const vector<TYPE> & q, const vector<TYPE> & p)
{
    auto a = q.cbegin();
    auto b = p.cbegin();
    
    while (a != q.cend()  && b != p.cend() )
    {
        if (*a != *b)
        {
            break;
        }
        ++a;
        ++b;
    }
    if (a == q.cend() )
    {
        return false;
    }
    if (b == p.cend() )
    {
        return true;
    }
    return *a < *b;
}


template <typename TYPE>
bool operator <= (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return (p < q) || (p == q);
}

template <typename TYPE>
bool operator > (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return ! (p <= q);
}

template <typename TYPE>
bool operator >= (const vector<TYPE> & q, const vector<TYPE> & p)
{
    return ! (p < q);
}


// produces an empty string of length d
string EmptyString (unsigned long d)
{
    return string (d, ' ');
}


// produces a string out of a single vector
string to_string (const vector<unsigned long> & k)
{

    if (k.empty() )
    {
        return "()";
    }
    string output = "(";
    for (auto && i : k)
    {
        output += to_string (i) + " ";
    }
    output.pop_back();
    output += ")";
    return output;
}
//produces a string out of a double vector
string to_string (const vector<vector<unsigned long>> & k)
{
    if (k.empty() )
    {
        return "()";
    }
    string output = "(";
    for (auto && i : k)
    {
        output += to_string (i) + " ";
    }
    output.pop_back();
    output += ")";
    return output;
}


string to_string (const vector<tuple<int, SingleSequence, SingleSequence>> & r)
{
    string output;
    for (auto && i : r)
    {
        if (std::get<0> (i) == 2)
        {
            output += to_string (std::get<2> (i) );
        }
        else if (std::get<0> (i) == 1)
        {
            output += to_string (std::get<1> (i) );
        }
        else
        {
            output += "-1";
        }
    }
    return output;
}

string to_string (const vector<tuple<int, SingleSequence, Level_21_Desc>> & r);



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
    friend class LevelThreeTree;
    template <typename>
    friend class LevelTwoTreeBasedDesc;
    
    friend void Flatten (Tree<unsigned long> &);
    template <typename VALUETYPE>
    friend void Flatten (FuncTree<unsigned long, VALUETYPE> & f);
    template <typename VALUETYPE>
    friend void Flatten (FuncTree<SingleSequence, VALUETYPE> & f);
    
private:
    TYPE                    last_entry;
    unsigned                length;
    
    TreeNode *              parent;
    
    unsigned long           number_of_children;
    
    TreeNode *              first_child;
    TreeNode *              last_child;
    
    TreeNode *              left;
    TreeNode *              right;
    TreeNode *              BKleft;
    TreeNode *              BKright;
    
public:

    ~TreeNode() = default;
    
    TreeNode() = delete;
    // we never create a new node from without parameters
    /*
        TreeNode () :
            // by default, creates the empty node
            // the entry of the emty is NOT DEFINED!
            // DON'T READ THE ENTRY OF THE EMPTY NODE!
            //
     //       entry (TYPE () ),
            parent (nullptr),
            number_of_children (0),
            first_child (nullptr),
            last_child (nullptr),
            left (nullptr),
            right (nullptr),
            BKleft (nullptr),
            BKright (nullptr)
        {}
    */
    // create a node with entry "e" and number of children "c" and length "l"
    // using universal reference
    //
    template <typename A>
    TreeNode (A && e, unsigned l = 0,
              unsigned long c = 0) :
        last_entry (std::forward<A> (e) ),
        length (l),
        parent (nullptr),
        number_of_children (c),
        first_child (nullptr),
        last_child (nullptr),
        left (nullptr),
        right (nullptr),
        BKleft (nullptr),
        BKright (nullptr)
    {}
    
    
    TreeNode (const TreeNode & s) :
        //only copy the entry of s, the number of children of s
        last_entry (s.last_entry),
        length (s.length),
        parent (nullptr),
        number_of_children (s.number_of_children),
        first_child (nullptr),
        last_child (nullptr),
        left (nullptr),
        right (nullptr),
        BKleft (nullptr),
        BKright (nullptr)
    {}
    
    friend void swap (TreeNode & s, TreeNode & t)
    {
        swap (s.entry, t.entry);
        std::swap (s.length, t.length);
        std::swap (s.parent, t.parent);
        std::swap (s.number_of_children, t.number_of_children);
        std::swap (s.first_child, t.first_child);
        std::swap (s.last_child, t.last_child);
        std::swap (s.left, t.left);
        std::swap (s.right, t.right);
        std::swap (s.BKleft, t.BKleft);
        std::swap (s.BKright, t.BKright);
    }
    
    TreeNode (TreeNode && s)
    //only copy the entry of s, the number of children of s
    {
        swap (*this, s);
    }
    
    const TYPE & LastEntry() const
    {
        return last_entry;
    }
    
    const unsigned & Length() const
    {
        return length;
    }
    
    //compare the entries only, provided TYPE can be compared
    //
    bool  operator == (const TreeNode & p) const
    {
        return last_entry == p.last_entry;
    }
    bool  operator != (const TreeNode & p) const
    {
        return last_entry != p.last_entry;
    }
    bool  operator < (const TreeNode & p) const
    {
        return last_entry < p.last_entry;
    }
    bool  operator > (const TreeNode & p) const
    {
        return last_entry > p.last_entry;
    }
    bool  operator <= (const TreeNode & p) const
    {
        return last_entry <= p.last_entry;
    }
    bool  operator >= (const TreeNode & p) const
    {
        return last_entry >= p.last_entry;
    }
    /*
        void MakeEntry (const TYPE & e)
        {
            entry = e;
        }*/
    
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
    // don't read the entry, but check if its parent pointer isnullptr
    
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
    template<typename, typename>
    friend class FuncTree;
    friend class LevelThreeTree;
    template <typename>
    friend class LevelTwoTreeBasedDesc;
    friend void Flatten (Tree<unsigned long> & f);
    
    template <typename VALUETYPE>
    void Flatten (FuncTree<unsigned long, VALUETYPE> &);
    
    
public:

    unsigned long cardinality;
    TreeNode<TYPE> * root;
    
public:
    // create a tree with cardinality c and root r
    //      the other nodes have been constructed elsewhere
    //
    Tree (unsigned long c, TreeNode<TYPE> * r) :
        cardinality (c),
        root (r)
    {}
    
    unsigned long RankAmongSiblings (const TreeNode<TYPE>* const s) const
    {
        unsigned long r = 0;
        auto current = s->Left();
        while (current != nullptr)
        {
            ++r;
            current = current->Left();
        }
        return r;
    }
    
    TreeNode<TYPE>* NodeInNaturalNumberOrder (const vector<unsigned long> & s) const
    {
    
        auto current = root;
        for ( auto && i : s)
        {
            current = current->FirstChild();
            for (unsigned long j = 0; j < i; ++ j)
            {
                current = current->right;
            }
        }
        return current;
    }
    
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
        
        if (s->IsNonEmpty() )
        {
            newnode->BKright = s;
            
            if (! (s->IsBKLeftMost() ) )
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

    void MakeNewSiblingLeft (TreeNode<TYPE> * const s,
                             TreeNode<TYPE> * const newnode)
    {
        ++ cardinality;
        
        // set new number of children
        ++ s->parent->number_of_children;
        
        //starting setting the BK order
        // move alongs s upwards to the place with a elder sister, if possible
        auto current = s;
        while (current->IsNonEmpty() )
        {
            if (current->IsLastBitLeftMost() )
            {
                current = current->parent;
            }
            else
            {
                break;
            }
        }
        if (current->IsEmpty() )
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

    friend void swap (Tree & S, Tree & T)
    {
        std::swap (S.root, T.root);
        std::swap (S.cardinality, T.cardinality);
    }
    
    // move the tree T to mine
    //  initialize well because after exchange, it will be desrtoryed by nontrivial ~Tree()
    Tree (Tree && T) :
        cardinality (0),
        root (nullptr)
    {
        swap (*this, T);
    }
    
    Tree& operator = (Tree T)
    {
        swap (*this, T);
        return *this;
    }
    
    Tree (const TYPE & root_entry = TYPE() ) :
        cardinality (1) ,
        root (new TreeNode<TYPE> (root_entry) )
    {}
    // by default, cardinality is the smallest possible (1),
    // and root_entry is either provided or the default TYPE
    
    Tree (const Tree & T) :
        // copy the tree T
        cardinality (T.cardinality)
    {
        vector<const TreeNode<TYPE> * > a;
        vector<TreeNode<TYPE> * > b;
        a.reserve (T.cardinality);
        b.reserve (T.cardinality);
        const TreeNode<TYPE> * current (T.Root() );
        while (current != nullptr)
        {
            a.emplace_back (current);
            b.emplace_back (new TreeNode<TYPE> (*current) );
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
        if (root == nullptr)
        {
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
    
    
    unsigned Length (const TreeNode<TYPE>* const s) const
    {
        return s->length;
    }
    
    vector<TYPE> EntireEntry (const TreeNode<TYPE>* const s) const
    {
        auto output = vector<TYPE> ();
        auto current = s;
        while (current->IsNonEmpty() )
        {
            output.emplace_back (current->LastEntry() );
            current = current->parent;
        }
        reverse (output.begin(), output.end() );
        return output;
    }
    
    string to_string (const TreeNode<TYPE>* const s) const
    // writes the entry of s into a string
    {
        auto && h = EntireEntry (s);
        if (h.size() == 0)
        {
            return "()";
        }
        string output = "(";
        for (auto && i : h)
        {
            output += ::to_string (i) + " ";
        }
        output.pop_back();
        output += ")";
        return output;
    }
    
    
    void Show (const TreeNode<TYPE>* const s) const
    {
        cout << "Node: " << to_string (s) << endl;
        cout << "number of children: " << s->number_of_children << endl;
        if (s->BKleft == nullptr)
        {
            cout << "  BKleft is nullptr" << endl;
        }
        else
        {
            cout << "  BKleft: " << to_string (s->BKleft) << endl;
        }
        if (s->BKright == nullptr)
        {
            cout << "  BKright is nullptr" << endl;
        }
        else
        {
            cout << "  BKright: " << to_string (s->BKright) << endl;
        }
        if (s->parent == nullptr)
        {
            cout << "  parent is nullptr" << endl;
        }
        else
        {
            cout << "  parent: " << to_string (s->parent) << endl;
        }
        if (s->first_child == nullptr)
        {
            cout << "  first_child is nullptr" << endl;
        }
        else
        {
            cout << "  first_child: " << to_string (s->first_child) << endl;
        }
        if (s->last_child == nullptr)
        {
            cout << "  last_child is nullptr" << endl;
        }
        else
        {
            cout << "  last_child: " << to_string (s->last_child) << endl;
        }
        if (s->left == nullptr)
        {
            cout << "  left is nullptr" << endl;
        }
        else
        {
            cout << "  left: " << to_string (s->left) << endl;
        }
        if (s->right == nullptr)
        {
            cout << "  right is nullptr" << endl;
        }
        else
        {
            cout << "  right: " << to_string (s->right) << endl;
        }
    }
    
    void ShowDomain (const TreeNode<TYPE>* const s) const
    {
        cout << "Node: " <<::to_string (s->last_entry.first) << endl;
        cout << "number of children: " << s->number_of_children << endl;
        if (s->BKleft == nullptr)
        {
            cout << "  BKleft is nullptr" << endl;
        }
        else
        {
            cout << "  BKleft: " <<::to_string (s->BKleft->last_entry.first) << endl;
        }
        if (s->BKright == nullptr)
        {
            cout << "  BKright is nullptr" << endl;
        }
        else
        {
            cout << "  BKright: " <<::to_string (s->BKright->last_entry.first) << endl;
        }
        if (s->parent == nullptr)
        {
            cout << "  parent is nullptr" << endl;
        }
        else
        {
            cout << "  parent: " <<::to_string (s->parent->last_entry.first) << endl;
        }
        if (s->first_child == nullptr)
        {
            cout << "  first_child is nullptr" << endl;
        }
        else
        {
            cout << "  first_child: " <<::to_string (s->first_child->last_entry.first) << endl;
        }
        if (s->last_child == nullptr)
        {
            cout << "  last_child is nullptr" << endl;
        }
        else
        {
            cout << "  last_child: " <<::to_string (s->last_child->last_entry.first) << endl;
        }
        if (s->left == nullptr)
        {
            cout << "  left is nullptr" << endl;
        }
        else
        {
            cout << "  left: " <<::to_string (s->left->last_entry.first) << endl;
        }
        if (s->right == nullptr)
        {
            cout << "  right is nullptr" << endl;
        }
        else
        {
            cout << "  right: " <<::to_string (s->right->last_entry.first) << endl;
        }
    }
    
    
    void Show (string name = "") const
    {
        cout << name << " has cardinality " << Cardinality() << "." << endl;
        cout << "The nodes are:" << endl;
        for (auto i = Root(); i != nullptr; i = NextEnumerate (i) )
        {
            Show (i);
        }
    }
    void ShowDomain (string name = "") const
    {
        cout << name << " has cardinality " << Cardinality() << "." << endl;
        cout << "The nodes are:" << endl;
        for (auto i = Root(); i != nullptr; i = NextEnumerate (i) )
        {
            ShowDomain (i);
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
        while (current->HasChild() )
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
        while (current->HasChild() )
        {
            current = current->first_child;
            output . emplace_back (current->LastEntry() );
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
            if (current->last_entry != compared->last_entry)
                return false;
            //once the node under comparison agree on number of children and  entry, continue
            current = NextEnumerate (current);
            compared = NextEnumerate (compared);
            // as long as "number_of_children" agree by far, they both point to the correct nodes
        }
        return true;
        //finished comparing
    }
    
    
    bool operator != (const Tree & T) const
    {
        return ! (*this == T);
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
    
    TreeNode<TYPE> * NextEnumerate (TreeNode<TYPE> * const s) const
    // enumerate the nodes of the tree in the dictionary order, NOT BK ORDER!
    {
        if (s->HasChild() )
        {
            return s->first_child;
        }
        TreeNode<TYPE> * current = s;
        
        while (current->IsNonEmpty() && current->IsLastBitRightMost() )
        {
            current = current->parent;
        }
        if (current->IsEmpty() )
            return nullptr;
            
        current = current->right;
        return current;
    }
    
//   bool ContainsElement(const TreeNode<TYPE> * const s) const;


    unsigned long Rank (const TreeNode<TYPE> * const s) const
    {
        unsigned long r = 0;
        auto current = s->BKLeft();
        while (current != nullptr)
        {
            ++r;
            current = current->BKLeft();
        }
        return r;
    }
    
    
//  trying universal reference and perfect forwarding
//
    template <typename A>
    TreeNode<TYPE> * AddChildBelow (TreeNode<TYPE> * const s,
                                    A && y)
    {
        // add a child below s with entry y
        // return the new child
        auto newnode = new TreeNode<TYPE> (std::forward<A> (y), s->length + 1) ;
        MakeNewChildBelow (s, newnode);
        return newnode;
    }
    
    template <typename A>
    TreeNode<TYPE> * AddSiblingLeft (TreeNode<TYPE> * const s,
                                     A && y)
    {
        // add an elder sister before s with entry y
        // return the elder sister
        auto newnode = new TreeNode<TYPE> (std::forward<A> (y), s->length);
        MakeNewSiblingLeft (s, newnode);
        return newnode;
    }
    
    template <typename A>
    TreeNode<TYPE> * Add (TreeNode<TYPE> * const s,
                          const DIRECTION & i,
                          A && y)
    {
        if (i == DIRECTION::DOWN)
        {
            return AddChildBelow (s, std::forward<A> (y) );
        }
        else
        {
            return AddSiblingLeft (s, std::forward<A> (y) );
        }
    }
    
    
    TreeNode<TYPE> * Remove (TreeNode<TYPE> * s)
    {
        // remove the terminal node , non-root ,
        // s must be terminal and non-root,
        // or the program will crash
        //
        // returns:  the parent of s, if s is the last child
        //         :  the first younger sister of s, if not
        
        if (s->IsLastBitRightMost() )
        {
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
        else
        {
            --cardinality;
            // the cardinality of myself -1
            
            auto parent = s->parent;
            auto right = s->right;
            
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
            if (parent->first_child == s)
            {
                parent->first_child = right;
            }
            //finished setting the children pointer of parent
            
            
            // setting the sibling order
            if (s->left == nullptr)
            {
                right->left = nullptr;
            }
            else
            {
                s->left->right = right;
                right->left = s->left;
            }
            //finished setting sibling order
            
            // free the memory taken by s
            delete s;
            
            //return the parent of the removed node
            return right;
        }
    }
    
    
    TreeNode<TYPE> * SpecialRemove (TreeNode<TYPE> * s)
    {
        auto output = Remove (s);
        auto temp = output->first_child;
        while (temp != nullptr)
        {
            temp->last_entry.first.pop_back();
            temp = temp->left;
        }
        return output;
    }
    
    TreeNode<TYPE> * MyNodeImmediateExtend (const TreeNode<TYPE>* const s, const TYPE & r) const
    {
        if (s->IsTerminal() )
        {
            return nullptr;
        }
        auto current = s->first_child;
        while (current != nullptr)
        {
            if (current->LastEntry() == r)
            {
                return current;
            }
            current = current->right;
        }
        return nullptr;
    }
    
    TreeNode<TYPE> * MyNode (const vector<TYPE> & r) const
    {
        TreeNode<TYPE> * current = Root();
        for (auto && i : r)
        {
            current = MyNodeImmediateExtend (current, i);
            if (current == nullptr)
            {
                return nullptr;
            }
        }
        return current;
    }
    
//    bool ContainsElement (const vector<TYPE> & r)
//    {
//        return MyNode (r) != nullptr;
//    }

};



template <typename ENTRYTYPE, typename VALUETYPE>
string to_string (const TreeNode<pair<ENTRYTYPE, VALUETYPE>> & k)
{
    string output = to_string (k.Entry().first);
    output += "|-->";
    output += to_string (k.Entry().second);
    return output;
}

// a template for a node of function whose domain is a tree
// domain takes vectors of ENTRYTYPE,
// image takes VALUETYPE
//

template <typename ENTRYTYPE, typename VALUETYPE>
const ENTRYTYPE & LastEntryInDomain (const TreeNode<pair<ENTRYTYPE, VALUETYPE>> & T)
{
    return T.LastEntry().first;
}

template <typename ENTRYTYPE, typename VALUETYPE>
const VALUETYPE & Value (const TreeNode<pair<ENTRYTYPE, VALUETYPE>> & T)
{
    return T.LastEntry().second;
}




// a template for a function whose domain is a tree
// domain takes vectors of ENTRYTYPE,
// image takes VALUETYPE
//
template <typename ENTRYTYPE, typename VALUETYPE>
class FuncTree : public Tree<pair<ENTRYTYPE, VALUETYPE>>
{

public:

    using Tree<pair<ENTRYTYPE, VALUETYPE>>::Tree;
    
//    VALUETYPE * Value(const Node<ENTRYTYPE> * const s) const;

//    void MakeValueAtNode(const Node<ENTRYTYPE> * const s, const VALUETYPE & y);

    // produces the domain of the function, which is a Tree<ENDRYTYPE>
    Tree<ENTRYTYPE> Domain() const
    {
        vector<const FuncTreeNode<ENTRYTYPE, VALUETYPE> * > a;
        vector<TreeNode<ENTRYTYPE> * > b;
        a.reserve (this->cardinality);
        b.reserve (this->cardinality);
        auto current = this->root;
        while (current != nullptr)
        {
            a.emplace_back (current);
            b.emplace_back (new TreeNode<ENTRYTYPE> (
                                current->LastEntry().first,
                                current->length,
                                current->number_of_children) );
                                
            // copy the entries , length and number_of_children first
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
        
        return Tree<ENTRYTYPE> (this->cardinality, b[0]);
        
    }
    
    
//    void MakeValueAtMyNode (TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s,
//                            const VALUETYPE & y)
//    {
//        s->Entry()->second = y;
//    }
//


    vector<ENTRYTYPE>   EntireEntryInDomain (
        const TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s) const
    {
        vector<ENTRYTYPE> output;
        auto current = s;
        while (current->IsNonEmpty() )
        {
            output.emplace_back (LastEntryInDomain (current) );
            current = current->Parent();
        }
        reverse (output.begin(), output.end() );
        return output;
    }
    
    
    
    string StringInDomain (const FuncTreeNode<ENTRYTYPE, VALUETYPE>* const s) const
    // writes the entry of domain component of s into a string
    {
        auto && h = EntireEntryInDomain (s);
        if (h.size() == 0)
        {
            return "()";
        }
        string output = "(";
        for (auto && i : h)
        {
            output += ::to_string (i) + " ";
        }
        output.pop_back();
        output += ")";
        return output;
    }
    
    
    
    FuncTreeNode<ENTRYTYPE, VALUETYPE> *
    MyNodeInDomainImmediateExtend (const FuncTreeNode<ENTRYTYPE, VALUETYPE>* const s,
                                   const ENTRYTYPE & r) const
    {
        if (s->IsTerminal() )
        {
            return nullptr;
        }
        auto current = s->FirstChild();
        while (current != nullptr)
        {
            if (LastEntryInDomain (current) == r)
            {
                return current;
            }
            current = current->Right();
        }
        return nullptr;
    }
    
    
    FuncTreeNode<ENTRYTYPE, VALUETYPE> * MyNodeInDomain (const vector<ENTRYTYPE> & r) const
    {
        auto current = this->Root();
        for (auto && i : r)
        {
            current = MyNodeInDomainImmediateExtend (current, i);
            if (current == nullptr)
            {
                return nullptr;
            }
        }
        return current;
    }
    
    
    const VALUETYPE & Value (const vector<ENTRYTYPE> & r) const
    {
        auto n = MyNodeInDomain (r);
        return Value (n);
    }
    
    const ENTRYTYPE & LastEntryInDomain (const FuncTreeNode<ENTRYTYPE, VALUETYPE> * s) const
    {
        return s->LastEntry().first;
    }
    
    const VALUETYPE & Value (const FuncTreeNode<ENTRYTYPE, VALUETYPE> * const s) const
    {
        return s->LastEntry().second;
    }
    
//    bool ContainsElementInDomain (const vector<ENTRYTYPE> & r) const
//    {
//        return MyNodeInDomain (r) != nullptr;
//    }

    template <typename A, typename B>
    TreeNode<pair<ENTRYTYPE, VALUETYPE>>* AddChildBelow (
                                          TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s,
                                          A && x,
                                          B && y)
    {
        return Tree<pair<ENTRYTYPE, VALUETYPE>>::AddChildBelow (
                   s, pair<ENTRYTYPE, VALUETYPE> ( std::forward<A> (x), std::forward<B> (y) ) );
    }
    
    template <typename A, typename B>
    TreeNode<pair<ENTRYTYPE, VALUETYPE>>* AddSiblingLeft (
                                          TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s,
                                          A && x,
                                          B && y)
    {
        return Tree<pair<ENTRYTYPE, VALUETYPE>>::AddSiblingLeft (
                   s, pair<ENTRYTYPE, VALUETYPE> ( std::forward<A> (x), std::forward<B> (y) ) );
    }
    
    template <typename A, typename B>
    TreeNode<pair<ENTRYTYPE, VALUETYPE>>* Add (
                                          TreeNode<pair<ENTRYTYPE, VALUETYPE>> * const s,
                                          const DIRECTION i,
                                          A && x,
                                          B && y)
    {
        return Tree<pair<ENTRYTYPE, VALUETYPE>>::Add (
                   s, i, pair<ENTRYTYPE, VALUETYPE> (std::forward<A> (x), std::forward<B> (y) ) );
    }
};

// a template of adding child below in a function
// based on a single tree
// just need the value
//
// testing universal reference again
//
template <typename VALUETYPE, typename A>
FuncTreeNode<unsigned long, VALUETYPE> * AddChildBelow (
    FuncTree<unsigned long, VALUETYPE> & f,
    FuncTreeNode<unsigned long, VALUETYPE> * const s,
    A && new_in_image)
{
    auto && next_entry = s->NumberOfChildren();
    return f.AddChildBelow (s, next_entry, std::forward<A> (new_in_image) );
}

template <typename VALUETYPE, typename A>
FuncTreeNode<unsigned long, VALUETYPE> * AddChildBelow (
    FuncTree<unsigned long, VALUETYPE> & f,
    const SingleSequence & s,
    A && new_in_image)
{
    return AddChildBelow (f, f.MyNodeInDomain (s), std::forward<A> (new_in_image) );
}

void Flatten (Tree<unsigned long> & f)
{
    if (f.IsTrivial() )
        return;
    TreeNode<unsigned long> * current = f.SmallestNode();
    current->parent = f.root;
    f.root->first_child = current;
    
    unsigned long r = 0;
    
    while (current->BKright != f.Root() )
    {
        TreeNode<unsigned long> * next = current->BKright;
        current->right = next;
        next->left = current;
        
        current->parent = f.root;
        
        current->length = 1;
        current->last_entry = r;
        ++r;
        current = current->BKright;
    }
    current->last_entry = r;
}

template <typename VALUETYPE>
void Flatten (FuncTree<unsigned long, VALUETYPE> & f)
{
    if (f.IsTrivial() )
        return;
    FuncTreeNode<unsigned long, VALUETYPE> * current = f.SmallestNode();
    current->parent = f.root;
    f.root->first_child = current;
    
    unsigned long r = 0;
    
    while (current->BKright != f.Root() )
    {
        FuncTreeNode<unsigned long, VALUETYPE> * next = current->BKright;
        current->right = next;
        next->left = current;
        
        current->parent = f.root;
        
        current->length = 1;
        current->last_entry.first = r;
        ++r;
        current = current->BKright;
    }
    current->last_entry.first = r;
}

template <typename VALUETYPE>
void Flatten (FuncTree<SingleSequence, VALUETYPE> & f)
{
    FuncTreeNode<SingleSequence, VALUETYPE> * current = f.Root()->FirstChild();
    while (current != nullptr)
    {
        current->last_entry.first = SingleSequence {f.RankAmongSiblings (current) };
        current = f.NextEnumerate (current);
    }
}


// a template of adding child below in a function
// based on a double tree
// just need the value
//
template <typename VALUETYPE, typename A>
FuncTreeNode<SingleSequence, VALUETYPE> * AddChildBelow (
    FuncTree<SingleSequence, VALUETYPE> & f,
    FuncTreeNode<SingleSequence, VALUETYPE> * const s,
    A && new_in_image)
{
    SingleSequence next_entry;
    if (s->NumberOfChildren() == 0)
    {
        next_entry = vector<unsigned long> {0};
    }
    else
    {
        auto && last_child_last_entry = s->LastChild()->LastEntry().first;
        next_entry = vector<unsigned long> {last_child_last_entry[0] + 1};
    }
    return f.AddChildBelow (s, next_entry, std::forward<A> (new_in_image) );
}


bool IsProperInitialSegment (const vector<unsigned long> & a,
                             const vector<unsigned long> & b)
{

    if (a.size() >= b.size() )
    {
        return false;
    }
    for (unsigned i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
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
template <typename VALUETYPE, typename A>
FuncTreeNode<SingleSequence, VALUETYPE> * AddSiblingLeft (
    FuncTree<SingleSequence, VALUETYPE> & f,
    FuncTreeNode<SingleSequence, VALUETYPE> * const s,
    A && new_in_image)
{
    SingleSequence next_entry;
    if (s->Left() == nullptr)
    {
        next_entry = s->LastEntry().first;
        next_entry . emplace_back (0);
    }
    else
    {
        auto && left_last_entry = s->Left()->LastEntry().first;
        const auto & last_entry = s->LastEntry().first;
        // maybe left is one-node extension of
        // maybe not
        if (IsProperInitialSegment (last_entry, left_last_entry) )
        {
            next_entry = left_last_entry;
            next_entry.back() += 1;
        }
        else
        {
            next_entry = last_entry;
            next_entry.emplace_back (0);
        }
    }
    return f.AddSiblingLeft (s, next_entry, std::forward<A> (new_in_image) );
}



// a template of adding  a point in a function
// based on a double tree
// need direction : down or left
// just need the value
//
template <typename VALUETYPE, typename A>
FuncTreeNode<SingleSequence, VALUETYPE> * Add (
    FuncTree<SingleSequence, VALUETYPE> & f,
    FuncTreeNode<SingleSequence, VALUETYPE> * const s,
    const DIRECTION i,
    A && new_in_image)
{

    if (i == DIRECTION::DOWN)
    {
        return AddChildBelow (f, s, std::forward<A> (new_in_image) );
    }
    else
    {
        return AddSiblingLeft (f, s, std::forward<A> (new_in_image) );
    }
    
}

template <typename VALUETYPE, typename A>
FuncTreeNode<SingleSequence, VALUETYPE> * Add (
    FuncTree<SingleSequence, VALUETYPE> & f,
    const vector<SingleSequence> & s,
    const DIRECTION i,
    A && new_in_image)
{
    return Add (f, f.MyNodeInDomain (s) , i, std::forward<A> (new_in_image) );
}

class LevelOneTree : public Tree<unsigned long>
{
    //a level-1 tree
    
public:
    string to_string (const unsigned & d = 0) const
    {
        string output = EmptyString (d);
        for (auto && i = SmallestNode();
                i != Root();
                i = i->BKRight() )
        {
            output += ::to_string (EntireEntry (i) );
        }
        return output;
    }
    
    LevelOneTree (const Tree& T) :
        Tree<unsigned long>::Tree (T) {};
        
    LevelOneTree () = default;
    
    LevelOneTree (const LevelOneTree & P) = default;
    
    LevelOneTree (LevelOneTree && P) :
        Tree<unsigned long> (std::move (P) ) {}
        
    LevelOneTree & operator  = (LevelOneTree P)
    {
        swap (*this, P);
        return *this;
    }
    
    LevelOneTreeNode * AddChildBelow (LevelOneTreeNode * const s)
    {
        return Tree<unsigned long>::AddChildBelow (s, s->NumberOfChildren() );
    }
    LevelOneTreeNode * AddChildBelow (const SingleSequence & s)
    {
        return AddChildBelow (MyNode (s) );
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
    void Input (const string name = "", const unsigned long d = 0)
    {
    
        auto current = Root();
        cout << EmptyString (d) << "Input the level-1 tree " << name << endl;
        while (true)
        {
            cout << EmptyString (d + indent) << "How many immediate successors of " << ::to_string (EntireEntry (current) ) << " ? ";
            unsigned long k;
            cin >> k;
            
            if (k == 0)
            {
                if (current->IsEmpty() )
                {
                    cout << EmptyString (d) << "Level-1 tree " << name << " input complete!" << endl;
                    return;
                }
                while (current->IsLastBitRightMost() )
                {
                    current = current->parent;
                    if (current->IsEmpty() )
                    {
                        cout << EmptyString (d) << "Level-1 tree " << name << " input complete!" << endl;
                        return;
                    }
                }
                current = current->right;
            }
            else
            {
                for (unsigned i = 0; i < k; ++i)
                {
                    AddChildBelow (current);
                }
                current = current->first_child;
            }
        }
    }
    
    SingleSequence CreateHangingSequenceFromUCF (const SingleSequence & w) const
    {
        auto n = MyNode (w);
        SingleSequence output = w;
        output.emplace_back (n->NumberOfChildren() );
        return output;
    }
    
    SingleSequence CreateHangingSequenceFromUCF (const LevelOneTreeNode* s) const
    {
        SingleSequence output = EntireEntry (s);
        output.emplace_back (s->NumberOfChildren() );
        return output;
    }
    
    
    PartialLevelOneTree CreatePartialExtensionFromUCF() const;
    PartialLevelOneTree CreatePartialExtensionFromUCF (const SingleSequence & s) const;
    PartialLevelOneTree CreatePartialExtensionFromUCF (const LevelOneTreeNode * const s) const;
    
    vector<PartialLevelOneTree> CreatePartialExtensions () const;
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
    
    
    PartialLevelOneTree (PartialLevelOneTree&& P)
    {
        swap (*this, P);
    }
    
    friend void swap (PartialLevelOneTree & M, PartialLevelOneTree & P)
    {
        swap (M.tree, P.tree);
        std::swap (M.node_minus, P.node_minus);
    }
    
    PartialLevelOneTree& operator= (PartialLevelOneTree P)
    {
        swap (*this, P);
        return *this;
    }
    
    PartialLevelOneTree() :
        tree (LevelOneTree () ),
        node_minus (tree.Root() )
    {}
    //by default, makes a tree empty and an empty node.
    // empty node is the ucf.
    
    PartialLevelOneTree (const PartialLevelOneTree & PP) :
        tree (PP.tree)
    {
        if (PP.node_minus == nullptr)
        {
            node_minus = nullptr;
        }
        else
        {
            node_minus = tree.MyNode (PP.SequenceMinus() );
        }
    }
    
    //create a partial level <=1 tree of degree 0 from P
    PartialLevelOneTree (const LevelOneTree & P) :
        tree (P),
        node_minus (nullptr)
    {}
    PartialLevelOneTree (LevelOneTree && P) :
        tree (std::move (P) ),
        node_minus (nullptr)
    {}
    
    // create a pratil level <= 1 tree of degree 1
    //  from P and the ucf s
    PartialLevelOneTree (const LevelOneTree & P, const SingleSequence & s) :
        tree (P),
        node_minus (tree.MyNode (s) )
    {}
    PartialLevelOneTree (LevelOneTree && P, const SingleSequence & s) :
        tree (std::move (P) ),
        node_minus (tree.MyNode (s) )
    {}
    
    // create a pratil level <= 1 tree of degree 1
    //  from P and the node in P
    PartialLevelOneTree (const LevelOneTree & P, const LevelOneTreeNode * const s) :
        tree (P),
        node_minus (tree.MyNode (P.EntireEntry (s) ) )
    {}
    PartialLevelOneTree (LevelOneTree && P, const LevelOneTreeNode * const s) :
        tree (std::move (P) ),
        node_minus (tree.MyNode (P.EntireEntry (s) ) )
    {}
    
    bool IsTrivial() const;
    DEGREE Degree() const
    {
        return (node_minus == nullptr) ? (DEGREE::ZERO) : (DEGREE::ONE);
    }
    
    const LevelOneTree & Tree() const
    {
        return tree;
    }
    
    LevelOneTreeNode * NodeMinusInTree () const
    {
        return node_minus;
    }
    
    SingleSequence SequenceMinus() const
    {
        return tree.EntireEntry (node_minus);
    }
    
    unsigned long Cardinality() const
    {
        return Tree().Cardinality() + 1;
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
        return (tree == P.tree && tree.EntireEntry (node_minus) == P.tree.EntireEntry (node_minus) );
    }
    bool operator != (const PartialLevelOneTree & P) const
    {
        return ! (*this == P);
    }
    
    bool IsPartialSubtree (const PartialLevelOneTree & P) const;
    
    
    // only apply to degree 1, only ontput the compleiton
    LevelOneTree Completion() const
    {
        auto u = tree;
        u.AddChildBelow (SequenceMinus() );
        return u;
    }
    
    // only apply to degree 1, outputs the completion,
    //   and the new node in the completion
    FinalTreeWithNode CompletionWithNode () const
    {
        auto u = tree;
        auto s = u.AddChildBelow (SequenceMinus() );
        return FinalTreeWithNode (std::move (u), s );
    }
    
    
    // only apply to degree 1
    SingleSequence CreateHangingSequence() const
    {
        return tree.CreateHangingSequenceFromUCF (node_minus );
    }
};


PartialLevelOneTree LevelOneTree::CreatePartialExtensionFromUCF() const
{
    return PartialLevelOneTree (*this);
}

PartialLevelOneTree LevelOneTree::CreatePartialExtensionFromUCF (
    const SingleSequence & s) const
{
    return PartialLevelOneTree (*this, CreateHangingSequenceFromUCF (s) );
}
PartialLevelOneTree LevelOneTree::CreatePartialExtensionFromUCF (
    const LevelOneTreeNode * const s) const
{
    return PartialLevelOneTree (*this, CreateHangingSequenceFromUCF (s) );
}

//vector<PartialLevelOneTree>   LevelOneTree::CreatePartialExtensions () const
//{
//    vector<PartialLevelOneTree> v;
//    v.emplace_back (PartialLevelOneTree (*this) );
//    for (auto i = Root()->FirstChild();
//            i != nullptr;
//            i = NextEnumerate (i) )
//    {
//        v.emplace_back (CreatePartialExtensionFromUCF (i) );
//    }
//    return v;
//}

class LevelTwoTree: public FuncTree < SingleSequence, PartialLevelOneTree>
{


private:

    //s is a node in the tree
    // add nodes below s whose domain forms a level-1 tree K
    void AddNodesBelowFromInput (const string & name,
                                 LevelTwoTreeNode * const s,
                                 const LevelOneTree & K,
                                 const int & d)
    {
    
    
        LevelOneTree  P { Value (s).Completion() };
        
        vector<SingleSequence> pp;
        
        //      pp->emplace_back(nullptr);
        
        for (auto p = P.Root()->first_child; p != nullptr; p = P.NextEnumerate (p) )
        {
            pp.emplace_back (P.EntireEntry (p) );
        }
        
        for (auto e = K.SmallestNode(); e != K.Root(); e = e->BKRight() )
        {
            cout << endl << EmptyString (d) << "Possible values of the node component of " << name << " at "
                 << ::to_string (K.EntireEntry (e) ) << ":" << endl;
                 
            for (unsigned long i = pp.size(); i != 0; --i)
            {
            
                auto newnode = P.CreateHangingSequenceFromUCF (pp [i - 1]);
                
                cout << EmptyString (d + indent) << pp.size() - i + 1 << ". "
                     << ::to_string (newnode);
            }
            cout << EmptyString (d + indent) << pp.size() + 1 << ". "
                 << "-1";
            cout << endl << EmptyString (d) << "Which one? ";
            unsigned long k;
            cin >> k;
            while (k <= 0 || k > pp.size() + 1)
            {
                cout << EmptyString (d) << "Error: Out of range! ";
                cin >> k;
            }
            if (k < pp.size() + 1)
            {
                FuncTree<SingleSequence, PartialLevelOneTree>::AddChildBelow (s,
                        K.EntireEntry (e),
                        PartialLevelOneTree (P,
                                             pp[pp.size() - k]) );
            }
            else
            {
                FuncTree<SingleSequence, PartialLevelOneTree>::AddChildBelow (s, K.EntireEntry (e), PartialLevelOneTree (P) );
            }
            
        }
    }
    
    
public:


    LevelTwoTree () = default;
    
    LevelTwoTree (const LevelTwoTree& Q) = default;
    
    LevelTwoTree (LevelTwoTree && f) :
        FuncTree<SingleSequence, PartialLevelOneTree> (std::move (f) )
    {}
    
    
    LevelTwoTree& operator= (LevelTwoTree T)
    {
        swap (*this, T);
        return *this;
    }
    
    
    ~LevelTwoTree() = default;
    
    const LevelTwoTreeNode * LeftWithSameHangingNode (const LevelTwoTreeNode * const s ) const
    {
        const LevelTwoTreeNode * output = s;
        do
        {
            output = output->Left();
        }
        while (output != nullptr && Value (output) == Value (s) );
        return output;
    }
    
    string to_string (const unsigned long & d = 0) const
    {
    
        auto current_tree = Root();
        auto temp_tree = current_tree;
        int depth = 0;
        string output;
        
        while (true)
        {
            temp_tree = temp_tree->LastChild();
            
            if (temp_tree != nullptr)
            {
                current_tree = temp_tree;
                
                ++ depth;
                
                vector<LevelTwoTreeNode*> history;
                
                auto record = current_tree->Parent();
                for (int a = depth - 1; a > 0; --a)
                {
                    history.emplace_back (record);
                    record = record -> Parent();
                }
                
                output += EmptyString (d);
                
                if (depth >= 2)
                {
                    for (int a = depth - 2; a >= 0; --a)
                    {
                        if (history[a]->IsLastBitLeftMost() )
                            output += " \t";
                        else
                            output += "|\t";
                    }
                }
                
                output += "+";
                output += string (interval, '-');
                if (Degree (current_tree) == DEGREE::ZERO)
                {
                    output += "(-1)";
                }
                else
                {
                    output += ::to_string (CreateHangingSequence (current_tree) );
                }
                output += "\n";
                
                continue;
            }
            
            while (current_tree != nullptr && current_tree->Left() == nullptr)
            {
                current_tree = current_tree->Parent();
                --depth;
                
            }
            
            if (current_tree == nullptr)
            {
                return output;
            }
            
            temp_tree = current_tree;
            current_tree = current_tree->Left();
            temp_tree = current_tree;
            
            vector<LevelTwoTreeNode*> history = vector<LevelTwoTreeNode*> ();
            auto record = current_tree->Parent();
            for (int a = depth - 1; a > 0; --a)
            {
                history.emplace_back (record);
                record = record -> Parent();
            }
            
            
            output += EmptyString (d);
            if (depth >= 2)
            {
            
                for (int a = depth - 2; a >= 0 ; --a)
                {
                    if (history[a]->IsLastBitLeftMost() )
                        output += " \t";
                    else
                        output += "|\t";
                }
            }
            output += "+";
            output += string (interval, '-');
            if (Degree (current_tree) == DEGREE::ZERO)
            {
                output += "(-1)";
            }
            else
            {
                output += ::to_string (CreateHangingSequence (current_tree) );
            }
            output += "\n";
            
        }
        return output;
        
    }
    
    //the degree of the partial level <=1 tree Q(s)
    DEGREE Degree (const LevelTwoTreeNode * const s) const
    {
        return Value (s).Degree();
    }
    DEGREE Degree (const DoubleSequence & s) const
    {
        return Value (MyNodeInDomain (s) ).Degree();
    }
    
    //the uniform cof of Q(s), i.e. the node-minus of Q(s)
    SingleSequence UCF (const DoubleSequence & s) const
    {
        return SequenceMinusValue (s);
    }
    
    //input the tree
    void Input (const string name = "", const unsigned long d = 0)
    {
    
    
        LevelTwoTreeNode * current = Root();
        
        while (true)
        {
            string nodename = ::to_string (EntireEntryInDomain (current) );
            
            
            LevelOneTree  K ;
            
            if (Degree (current) == DEGREE::ZERO)
            {
                cout << EmptyString (d) << nodename << " has degree 0. It must be terminal" << endl;
            }
            else
            {
                string level_1_tree_name = name + "{" + nodename + "}";
                cout << EmptyString (d) << "Immediate successors of " << name << " at "
                     << StringInDomain (current)
                     << " forms a level-1 tree " << level_1_tree_name  << " :" << endl;
                     
                     
                cout << endl;
                K.Input (level_1_tree_name , d + indent);
                cout << endl;
            }
            
            if (K.IsTrivial() )
            {
                if (current->IsEmpty() )
                {
                    cout << EmptyString (d) << "Level-2 tree " << name << " input complete!" << endl;
                    return;
                }
                while (current->IsLastBitRightMost() )
                {
                    current = current->parent;
                    if (current->IsEmpty() )
                    {
                        cout << EmptyString (d) << "Level-2 tree " << name << " input complete!" << endl;
                        return;
                    }
                }
                current = current->right;
            }
            else
            {
                AddNodesBelowFromInput (name, current, K, d);
                current = current->first_child;
            }
        }
    }
    
    //  bool ContainsInDomainStar (const TreeNode* const s) const;
    
    //the tree component of Q(s)
    const LevelOneTree & TreeValue (const DoubleSequence & s) const
    {
        return Value (s).Tree();
    }
    const LevelOneTree & TreeValue (const LevelTwoTreeNode * const s) const
    {
        return Value (s).Tree();
    }
    
    // the node minus value of Q(s)
    SingleSequence SequenceMinusValue (const DoubleSequence & s) const
    {
        return Value (s).SequenceMinus();
    }
    // the node minus value of Q(s)
    SingleSequence SequenceMinusValue (const LevelTwoTreeNode * const s) const
    {
        return Value (s).SequenceMinus();
    }
    
    //the hanging node of Q(s)
    SingleSequence CreateHangingSequence (const DoubleSequence & s) const
    {
        return Value (s).CreateHangingSequence();
    }
    //the hanging node of Q(s)
    SingleSequence CreateHangingSequence (const LevelTwoTreeNode * const s) const
    {
        return Value (s).CreateHangingSequence();
    }
    
    //the completion node of Q(s)
    LevelOneTree CreateCompletion (const DoubleSequence & s) const
    {
        return Value (s).Completion();
    }
    LevelOneTree CreateCompletion (const LevelTwoTreeNode * const s) const
    {
        return Value (s).Completion();
    }
    
    
    // the new node has degree 0
    // add child below
    LevelTwoTreeNode *  AddChildBelow (LevelTwoTreeNode * const s)
    {
        auto && completion = Value (s).Completion();
        auto && new_partial_tree = PartialLevelOneTree (std::move (completion) );
        
        return ::AddChildBelow (*this, s, std::move (new_partial_tree) );
    }
    
    LevelTwoTreeNode *  AddChildBelow (const DoubleSequence & s)
    {
        return AddChildBelow (this->MyNodeInDomain (s) );
    }
    
    
    // the new node has degree 1
    //add child below
    LevelTwoTreeNode *  AddChildBelow (LevelTwoTreeNode * const s,
                                       const SingleSequence & u)
    {
        auto && completion = Value (s).Completion();
        auto && new_partial_tree = PartialLevelOneTree (std::move (completion), u);
        
        return ::AddChildBelow (*this, s, std::move (new_partial_tree) );
    }
    LevelTwoTreeNode *  AddChildBelow (const DoubleSequence & s,
                                       const SingleSequence & u)
    {
        return AddChildBelow (this->MyNodeInDomain (s), u);
    }
    
    
    
    // the new node has degree 0
    // add an elder sister on the left
    LevelTwoTreeNode *  AddSiblingLeft (LevelTwoTreeNode * const s)
    {
        auto && completion = Value (s).Tree();
        auto && new_partial_tree = PartialLevelOneTree (std::move (completion) );
        
        return ::AddSiblingLeft (*this, s, std::move (new_partial_tree) );
    }
    
    LevelTwoTreeNode *  AddSiblingLeft (const DoubleSequence & s)
    {
        return AddSiblingLeft (this->MyNodeInDomain (s) );
    }
    
    
    // the new node has degree 1
    // add an elder sister on the left
    LevelTwoTreeNode *  AddSiblingLeft (LevelTwoTreeNode * const s,
                                        const SingleSequence & u)
    {
        auto && completion = Value (s).Tree();
        auto && new_partial_tree = PartialLevelOneTree (std::move (completion), u);
        
        return ::AddSiblingLeft (*this, s, std::move (new_partial_tree) );
    }
    LevelTwoTreeNode *  AddSiblingLeft (const DoubleSequence & s,
                                        const SingleSequence & u)
    {
        return AddSiblingLeft (this->MyNodeInDomain (s), u);
    }
    
    // the new node has degree 0
    // add
    LevelTwoTreeNode *  Add (LevelTwoTreeNode * const s,
                             const DIRECTION & direction)
    {
        if (direction == DIRECTION::DOWN)
            return AddChildBelow (s);
        else
            return AddSiblingLeft (s);
    }
    
    LevelTwoTreeNode *  Add (const DoubleSequence & s,
                             const DIRECTION & direction)
    {
        return Add (this->MyNodeInDomain (s) , direction);
    }
    
    
    // the new node has degree 1
    // add an elder sister on the left
    LevelTwoTreeNode *  Add (LevelTwoTreeNode * const s,
                             const DIRECTION & direction,
                             const SingleSequence & u)
    {
        if (direction == DIRECTION::DOWN)
            return AddChildBelow (s, u);
        else
            return AddSiblingLeft (s, u);
    }
    LevelTwoTreeNode *  Add (const DoubleSequence & s,
                             const DIRECTION & direction,
                             const SingleSequence & u)
    {
        return Add (this->MyNodeInDomain (s), direction, u);
    }
    
    
    FinalTreeWithNode CreateFinalTreeWithNodeFromUCF (
        const LevelTwoTreeNode * const s,
        const DIRECTION & i) const
    {
        if (i == DIRECTION::DOWN)
        {
            return Value (s).CompletionWithNode();
        }
        else
        {
            return Value (s->Parent() ).CompletionWithNode();
        }
    }
    FinalTreeWithNode CreateFinalTreeWithNodeFromUCF  (
        const DoubleSequence & s,
        const DIRECTION & i) const
    {
        return CreateFinalTreeWithNodeFromUCF (MyNodeInDomain (s), i);
    }
    
    // if i extend by adding a new node at direction i of s
    //      whta is the level-1 tree component of the new value?
    //
//    LevelOneTree ToBeExtended (const LevelTwoTreeNode * const s,
//                               const DIRECTION & i) const
//    {
//
//        if (i == DIRECTION::DOWN)
//        {
//            return Value (s).Tree();
//        }
//        else
//        {
//            return Value (s->Parent() ).Tree();
//        }
//    }

    // if s is a newly added element, what was the fainal teree with node
    //      previously when it was part of a partial level-2 tree?
    FinalTreeWithNode PresentFinalTreeWithNode (const LevelTwoTreeNode * s) const
    {
        if (s->Right() != nullptr)
        {
            return CreateFinalTreeWithNodeFromUCF (s->Right(),
                                                   DIRECTION::LEFT);
        }
        else
        {
            return CreateFinalTreeWithNodeFromUCF (s->Parent(),
                                                   DIRECTION::DOWN);
        }
    }
    // s is never empty node in this funciton
};

// make P a copy of Q
void MakeCopy (FinalTreeWithNode & P, const FinalTreeWithNode & Q)
{
    P.first = Q.first;
    P.second = P.first.MyNode (Q.first.EntireEntry (Q.second) );
}

// is s the BK pred of t?
// s,t are alraedy in W
//
bool IsBKPredecessor (const SingleSequence & s,
                      const SingleSequence & t,
                      const LevelOneTree & W)
{
    return (W.MyNode (s) == W.MyNode (t)->BKLeft() );
}



class Level_leq_2_Tree
{

public:

    string to_string (const Level_leq_2_TreeNode & q) const
    {
        if (std::get<0> (q) == DEGREE::ZERO)
        {
            return "(0, -1)";
        }
        if (std::get<0> (q) == DEGREE::ONE)
        {
            return "(1, " + ::to_string (tree_1.EntireEntry (std::get<1> (q) ) ) + ")";
        }
        return "(2, " + ::to_string (tree_2.EntireEntryInDomain (std::get<2> (q) ) ) + ")";
        
    }
    
    string to_string (const unsigned & d = 0) const
    {
        string output;
        output += EmptyString (d) ;
        output += "Level-1 component: ";
        output += ::to_string (tree_1);
        output += "\n";
        output += EmptyString (d) ;
        output += "Level-2 component:\n";
        output += ::to_string (tree_2, d + indent);
        return output;
    }
    
    LevelOneTree tree_1;
    LevelTwoTree tree_2;
    
public:
    Level_leq_2_Tree() :  
	tree_1 (LevelOneTree()),
	tree_2 (LevelTwoTree())
{}
    
    ~Level_leq_2_Tree() = default;
    
    Level_leq_2_Tree (const Level_leq_2_Tree & Q) :
        tree_1 (Q.tree_1),
        tree_2 (Q.tree_2)
    {}
    
    template <typename A, typename B>
    Level_leq_2_Tree (A && Q1, B && Q2) :
        tree_1 (std::forward<A> (Q1) ),
        tree_2 (std::forward<B> (Q2) )
    {}
    
    Level_leq_2_Tree (Level_leq_2_Tree && Q)
    //  :
//       tree_1 (LevelOneTree() ),
//       tree_2 (LevelTwoTree() )
    {
        swap (*this, Q) ;
    }
    
    friend void swap (Level_leq_2_Tree & P, Level_leq_2_Tree & Q)
    {
        swap (P.tree_1, Q.tree_1);
        swap (P.tree_2, Q.tree_2);
    }
    
    Level_leq_2_Tree & operator = (Level_leq_2_Tree Q)
    {
        swap (*this, Q);
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
        return ! (*this == Q);
    }
    
    void Input (const string name = "", const unsigned long d = 0)
    {
        cout << EmptyString (d) << "Input the level <=2 tree " << name << endl << endl;
        tree_1.Input (name + "1", d + indent);
        cout << endl;
        tree_2.Input (name + "2", d + indent);
        cout << endl;
        cout << EmptyString (d) << "Level <=2 tree " << name << " input complete!" << endl;
    }
    
    // the level <=2 node in my tree
    // when give s is degree 0 , outputs the degree 0 node
    Level_leq_2_TreeNode MyNode (const leq_2_Sequence s) const
    {
        if (std::get<0> (s) == DEGREE::ZERO)
        {
            return zeroLevel_leq_2_TreeNode;
        }
        else if (std::get<0> (s) == DEGREE::ONE)
        {
            return Level_leq_2_TreeNode (DEGREE::ONE,
                                         tree_1.MyNode (std::get<1> (s) ),
                                         nullptr);
        }
        else
        {
            return Level_leq_2_TreeNode (DEGREE::TWO,
                                         nullptr,
                                         tree_2.MyNodeInDomain (std::get<2> (s) ) );
        }
    }
    
    SingleSequence EntireEntry_1 (const Level_leq_2_TreeNode & s) const
    {
        return tree_1.EntireEntry (std::get<1> (s) );
    }
    
    DoubleSequence EntireEntryInDomain_2 (const Level_leq_2_TreeNode & s) const
    {
        return tree_2.EntireEntryInDomain (std::get<2> (s) );
    }
    
    leq_2_Sequence EntireEntry (const Level_leq_2_TreeNode & s) const
    {
        if (std::get<0> (s) == DEGREE::ZERO)
        {
            return zero_leq_2_Sequence;
        }
        
        if (std::get<0> (s) == DEGREE::ONE)
        {
            return leq_2_Sequence (DEGREE::ONE,
                                   EntireEntry_1 (s),
                                   DoubleSequence() );
        }
        else
        {
            return leq_2_Sequence (DEGREE::TWO,
                                   SingleSequence(),
                                   EntireEntryInDomain_2 (s) );
        }
    }
    
    // create a node whose ucf is given, (i,s)
    //
    leq_2_Sequence CreateHangingSequenceFromUCF (
        const Level_leq_2_TreeNode & s,
        const DIRECTION & i) const
    {
        if (std::get<0> (s) == DEGREE::ZERO)
        {
            return leq_2_Sequence (DEGREE::ZERO,
                                   SingleSequence(),
                                   DoubleSequence() );
        }
        if (std::get<0> (s) == DEGREE::ONE)
        {
            return leq_2_Sequence (DEGREE::ONE,
                                   CreateHangingSequenceFromUCF_1 (std::get<1> (s) ),
                                   DoubleSequence() );
        }
        else
        {
            return leq_2_Sequence (DEGREE::TWO,
                                   SingleSequence(),
                                   CreateHangingSequenceFromUCF_2 (std::get<2> (s) , i ) );
        }
    }
    leq_2_Sequence CreateHangingSequenceFromUCF (const leq_2_Sequence & s, const DIRECTION & i) const
    {
        return CreateHangingSequenceFromUCF (MyNode (s) , i);
    }
    
    
    //create a hanging node whose ucf is s
    SingleSequence CreateHangingSequenceFromUCF_1 (const LevelOneTreeNode * const s) const
    {
        return tree_1.CreateHangingSequenceFromUCF (s);
    }
    SingleSequence CreateHangingSequenceFromUCF_1 (const SingleSequence & s) const
    {
        return CreateHangingSequenceFromUCF_1 (tree_1.MyNode (s) );
    }
    
    
    
    // crate a hanging node whose ucf is (i,s)
    DoubleSequence CreateHangingSequenceFromUCF_2 (const LevelTwoTreeNode * const s, const DIRECTION & i) const
    {
        auto output = tree_2.EntireEntryInDomain (s);
        SingleSequence next_entry;
        
        if (i == DIRECTION::DOWN)
        {
            //going down
            if (s->NumberOfChildren() == 0)
            {
                next_entry = vector<unsigned long> {0};
            }
            else
            {
                auto last_child_last_entry = s->LastChild()->LastEntry().first;
                next_entry = vector<unsigned long> {last_child_last_entry[0] + 1};
            }
            output.emplace_back (next_entry);
        }
        else
        {
            // going left
            if (s->Left() == nullptr)
            {
                next_entry = s->LastEntry().first;
                next_entry . emplace_back (0);
            }
            else
            {
                auto left_last_entry = s->Left()->LastEntry().first;
                auto last_entry = s->LastEntry().first;
                // maybe left is one-node extension of
                // maybe not
                if (IsProperInitialSegment (last_entry, left_last_entry) )
                {
                    next_entry = left_last_entry;
                    next_entry.back() += 1;
                }
                else
                {
                    next_entry = last_entry;
                    next_entry.emplace_back (0);
                }
            }
            output.back() = next_entry;
        }
        
        return output;
    }
    DoubleSequence CreateHangingSequenceFromUCF_2 (const DoubleSequence & s, const DIRECTION & i) const
    {
        return CreateHangingSequenceFromUCF_2 (tree_2.MyNodeInDomain (s) , i);
    }
    
    
// if add a new node at s , direction i, what is the final tree with node?
//
    FinalTreeWithNode CreateFinalTreeWithNodeFromUCF (const leq_2_Sequence & s, const DIRECTION & i) const
    {
        if (std::get<0> (s) != DEGREE::TWO)
        {
            return FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        return tree_2.CreateFinalTreeWithNodeFromUCF (std::get<2> (s) , i);
    }
    FinalTreeWithNode CreateFinalTreeWithNodeFromUCF (const Level_leq_2_TreeNode & s, const DIRECTION & i) const
    {
        if (std::get<0> (s) != DEGREE::TWO)
        {
            return FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        return tree_2.CreateFinalTreeWithNodeFromUCF (std::get<2> (s) , i);
    }
};





template <typename A>
class LevelTwoTreeBasedDesc
{

    friend LevelOneTreeNode* BaseUCF (const LevelTwoTreeBasedDesc &,
                                      const LevelOneTree &);
                                      
public:
    STATE state;
    // is it valid or not?
    
    DEGREE degree;
    SingleSequence sequence_1;
    DoubleSequence sequence_2;
    // the discontinuous node
    //
    // having -1 case is
    // treated separately
    
    FuncTree<unsigned long, A> factor;
    // defalut if degree 1
    // we don't care anyway if degeree 1
    
public:
    vector<FuncTreeNode<unsigned long, A>*> enumeration;
    // the enumeratin of the domain of factor according to the order by level-2 tree
    
    FuncTreeNode<unsigned long, A> * ucf_at_domain;
    // the node of ucf at domain of factor, or nullptr
    // if nullptr, must be indeed a node of a factor, not some synonym
    //
    
public:
    ~LevelTwoTreeBasedDesc() = default;
    
    LevelTwoTreeBasedDesc (LevelTwoTreeBasedDesc&& D)
    //    LevelTwoTreeBasedDesc()
    {
        swap (*this, D);
    }
    
    friend void swap (LevelTwoTreeBasedDesc & C,
                      LevelTwoTreeBasedDesc & D)
    {
        std::swap (C.state, D.state);
        std::swap (C.degree, D.degree);
        std::swap (C.sequence_1, D.sequence_1);
        std::swap (C.sequence_2, D.sequence_2);
        swap (C.factor, D.factor);
        std::swap (C.enumeration, D.enumeration);
        std::swap (C.ucf_at_domain, D.ucf_at_domain);
    }
    
    LevelTwoTreeBasedDesc& operator= (LevelTwoTreeBasedDesc D)
    {
        swap (*this, D);
        return *this;
    }
    
    
    LevelTwoTreeBasedDesc (const STATE & s) :
        // only create an invalid desc
        state (STATE::INVALID)
    {}
    
    LevelTwoTreeBasedDesc() :
        state (STATE::VALID),
        degree (DEGREE::TWO) ,
        sequence_1 (SingleSequence() ) ,
        sequence_2 (DoubleSequence() ),
        factor (FuncTree<unsigned long, A>() ),
        enumeration (vector<FuncTreeNode<unsigned long, A>*> {factor.Root() }),
                ucf_at_domain (factor.Root() )
    {}
    
//    LevelTwoTreeBasedDesc (const LevelTwoTreeBasedDesc & D) :
//        state (STATE::VALID), //only copy a vailid desc!!
//        degree (D.degree),
//        sequence_1 (D.sequence_1),
//        sequence_2 (D.sequence_2),
//        factor (D.factor)
//    {
//        if (D.ucf_at_domain == nullptr)
//        {
//            ucf_at_domain = nullptr;
//        }
//        else
//        {
//            ucf_at_domain = factor.MyNodeInDomain (D.factor.EntireEntryInDomain (D.ucf_at_domain) );
//        }
//        for (auto && i : D.enumeration)
//        {
//            enumeration.emplace_back (factor.MyNodeInDomain (D.factor.EntireEntryInDomain (i) ) );
//        }
//    }

    LevelTwoTreeBasedDesc (const LevelTwoTreeBasedDesc & D) :
        state (STATE::VALID), //only copy a vailid desc!!
        degree (D.degree),
        sequence_1 (D.sequence_1),
        sequence_2 (D.sequence_2),
        enumeration (vector<FuncTreeNode<unsigned long, A>*> () ),
        ucf_at_domain (nullptr)
    {
    
        if (D.Degree() == DEGREE::TWO)
        {
        
            auto && T = D.factor;
            
            vector<const FuncTreeNode<unsigned long, A> * > a;
            vector<FuncTreeNode<unsigned long, A> * > b;
            a.reserve (T.cardinality);
            b.reserve (T.cardinality);
            for (auto && current : D.enumeration )
            {
                a.emplace_back (current);
                b.emplace_back (new FuncTreeNode<unsigned long, A> (current->last_entry,
                                current->length,
                                current->number_of_children) );
                // copy the entries and number_of_children first
            }
            
            //set links between nodes
            for (unsigned long i = 0; i < T.cardinality; ++i)
            {
                if (D.ucf_at_domain == a[i])
                {
                    ucf_at_domain = b[i];
                }
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
            
            factor =  FuncTree<unsigned long, A> (D.factor.cardinality, b[0]);
            //point the root to the copied root
            
            
            for (auto && i : b)
            {
                enumeration.emplace_back (i);
            }
        }
    }
    
    LevelTwoTreeBasedDesc (const SingleSequence & n)   :
        //construct degree 1
        state (STATE::VALID),
        degree (DEGREE::ONE) ,
        sequence_1 (n),
        sequence_2 (DoubleSequence() ),
        ucf_at_domain (nullptr)
    {}
    /*
        LevelTwoTreeBasedDesc (const DoubleSequence & n,
                               const FuncTree<unsigned long, A> & f,
                               const vector<SingleSequence> & e,
                               const SingleSequence & u) :
            //constructs degree 2, discontinuous type
            LevelTwoTreeBasedDesc (n, f, e)
        {
            ucf_at_domain = factor.MyNodeInDomain (u);
        }
    
        LevelTwoTreeBasedDesc (const DoubleSequence & n,
                               const FuncTree<unsigned long, A> & f,
                               const vector<SingleSequence> & e) :
            //constructs degree 2, continuous type
            degree (DEGREE::TWO),
            sequence_1 (SingleSequence()),
            sequence_2 (n),
            factor (f),
            ucf_at_domain (nullptr)
        {
            for (auto && i : e)
            {
                enumeration.emplace_back (factor.MyNodeInDomain (i));
            }
        }*/
    
    bool IsValid() const
    {
        return state == STATE::VALID;
    }
    
    DEGREE Degree() const
    {
        return degree;
    }
    const SingleSequence & GetSequence_1() const
    {
        return sequence_1;
    }
    const DoubleSequence & GetSequence_2() const
    {
        return sequence_2;
    }
    const FuncTree<unsigned long, A> & GetFactor() const
    {
        return factor;
    }
    
    
    bool IsConstant() const
    // is it constant?
    {
        return degree == DEGREE::TWO && sequence_2.empty() && IsDiscontinuousTypeAtDomain();
    }
    
    bool IsContinuousTypeAtDomain() const
    // is it continuous typea t domain?
    {
        if (degree == DEGREE::ONE)
        {
            return false;
        }
        if (degree == DEGREE::TWO)
        {
            if (factor.Cardinality() == sequence_2.size() + 2)
            {
                return true;
            }
            
        }
        return false;
    }
    
    bool IsDiscontinuousTypeAtDomain() const
    // is it discontinuous typE?
    {
        return ! (IsContinuousTypeAtDomain() );
    }
    
    
    FuncTreeNode<unsigned long, A> * UCFAtDomain() const
    {
        return ucf_at_domain;
    }
    
    FuncTreeNode<unsigned long, A> * LastNodeInDomain () const
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
            return (sequence_1 == D.sequence_1);
        }
        if (sequence_2 != D.sequence_2)
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
        return ! (*this == D);
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
            return sequence_1 < D.sequence_1;
        }
        return Representation() < D.Representation();
    }
    
    bool operator <= (const LevelTwoTreeBasedDesc& D) const
    {
        return *this < D || *this == D;
    }
    bool operator > (const LevelTwoTreeBasedDesc& D) const
    {
        return ! (*this <= D);
    }
    bool operator >= (const LevelTwoTreeBasedDesc& D) const
    {
        return ! (*this < D);
    }
    
    
    vector<tuple<int, SingleSequence, A>> Representation() const
    {
        vector<tuple<int, SingleSequence, A>> out;
        if (degree == DEGREE::ONE)
        {
            cout << "you are trying to represent a level-21 desc of deg 1!" << endl;
            return out;
        }
        
        auto e = sequence_2.cbegin();
        
        for (auto && i = enumeration.cbegin() + 1; i != enumeration.cend(); ++i)
        {
            out.emplace_back ( 2, SingleSequence(), (*i)->Entry().second);
            if (e != sequence_2.cend() )
            {
                out.emplace_back ( 1, *e, A() );
                ++e;
            }
            else
            {
                out.emplace_back ( -1, SingleSequence(), A() );
                break;
            }
        }
        return out;
    }
    
    
    string to_string (const unsigned d = 0) const
    {
        //formats it into a string
        string s = EmptyString (d) + "degree: ";
        if (degree == DEGREE::ONE)
        {
            s += "1\n";
            s += EmptyString (d) + "node: " + ::to_string (sequence_1) + "\n";
        }
        else
        {
            s += "2\n";
            s += EmptyString (d) + "node: " + ::to_string (sequence_2);
            if (sequence_2.empty() )
            {
                if (IsContinuousTypeAtDomain() )
                {
                    s.pop_back();
                    s.pop_back();
                    s += "-1";
                }
            }
            else if (IsContinuousTypeAtDomain() )
            {
                s += " -1";
            }
            s += "\n";
        }
        if (degree == DEGREE::TWO)
        {
            s += EmptyString (d) + "factor map:\n";
            for (auto && p : enumeration )
            {
            
                string factor_string = ::to_string (factor.EntireEntryInDomain (p) );
                factor_string += "|-->";
                factor_string += ::to_string (factor.Value (p) );
                s += EmptyString (d + indent) + factor_string + "\n";
            }
//           s+= "Representation: "+ ::to_string(Representation()) + "\n";

        }
        
        return s;
    }
    
    string String221 (const unsigned d = 0) const
    {
        //formats it into a string
        string s = EmptyString (d) + "degree: ";
        if (degree == DEGREE::ONE)
        {
            s += "1\n";
            s += EmptyString (d) + "node: " + ::to_string (sequence_1) + "\n";
        }
        else
        {
            s += "2\n";
            s += EmptyString (d) + "node: " + ::to_string (sequence_2);
            if (sequence_2.empty() )
            {
                if (IsContinuousTypeAtDomain() )
                {
                    s.pop_back();
                    s.pop_back();
                    s += "-1";
                }
            }
            else if (IsContinuousTypeAtDomain() )
            {
                s.pop_back();
                s += " -1)";
            }
            s += "\n";
        }
        if (degree == DEGREE::TWO)
        {
            s += EmptyString (d) + "factor map:\n";
            for (auto &&  p : enumeration )
            {
            
                string factor_string = ::to_string (factor.EntireEntryInDomain (p) );
                factor_string += "|--> the following level-21 desc:\n" ;
                factor_string += factor.Value (p).to_string (d + indent);
                s += EmptyString (d + indent) + factor_string + "\n";
            }
//           s+= "Representation: "+ ::to_string(Representation()) + "\n";

        }
        
        return s;
    }
    
    void DiscontinuousTrim()
    {
        // if the node in the level-2 tree ends with -1
        //
        // remove the last node of factor and the -1
        
        if (IsContinuousTypeAtDomain() )
        {
            enumeration.pop_back();
            ucf_at_domain = factor.Remove (ucf_at_domain);
        }
    }
    
    // only the "new_in_image" could be a rvalue, to be moved
    // the "extend_node" part is taken from a tree, and we want to COPY it,
    // or we would ruin the tree
    //
    template<typename B>
    void Extend (const SingleSequence & extend_node,
                 B && new_in_image,
                 const SingleSequence & new_ucf)
    {
        // extend the current degree-2 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is not -1
        //
        
        Extend (extend_node, std::forward<B> (new_in_image) ); //to change interface later
        ucf_at_domain = factor.MyNodeInDomain (new_ucf);
    }
    
    template<typename B>
    void Extend (const SingleSequence & extend_node,
                 B && new_in_image)
    {
        // extend the current degree-21 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is -1
        //
        sequence_2.emplace_back (extend_node);
        
        auto && new_in_domain = AddChildBelow<A> (factor,
                                ucf_at_domain,
                                std::forward<B> (new_in_image) );
                                
        enumeration.emplace_back (new_in_domain);
        ucf_at_domain = nullptr;
    }
    
    
    
    template<typename B>
    void Extend (B && new_in_image)
    {
        // extend the current degree-2 desc by one
        //
        // must be discontinuous to start with
        // resulting in a new continuous desc
        //
        
        auto && new_in_domain = AddChildBelow<A> (factor,
                                ucf_at_domain,
                                std::forward<B> (new_in_image) );
                                
        enumeration.emplace_back (new_in_domain);
        ucf_at_domain = new_in_domain;
    }
    
    
    template<typename B>
    void Extend (const LevelTwoTree & Q,
                 const LevelTwoTreeNode * const q,
                 B && new_in_image)
    {
        if (q == nullptr)
        {
            Extend (new_in_image);
            return;
        }
        
        auto && add_sequence = q->LastEntry().first;
        
        if (Q.Degree (q) == DEGREE::ZERO)
        {
            Extend (add_sequence, std::forward<B> (new_in_image) );
        }
        else
        {
            auto && new_ucf = Q.SequenceMinusValue (q);
            Extend (add_sequence, std::forward<B> (new_in_image), new_ucf);
        }
    }
    
    
    
    template<typename B>
    void Extend (const Level_leq_2_Tree & Q,
                 const Level_leq_2_TreeNode & q,
                 B && new_in_image)
    {
    
        Extend (Q.tree_2, std::get<2> (q), std::forward<B> (new_in_image) );
    }
    
    
    
    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node,
                              const SingleSequence & new_ucf)
    {
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is not -1
        
        sequence_2.back() = last_entry_in_node;
        ucf_at_domain = factor.MyNodeInDomain (new_ucf);
    }
    
    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node)
    {
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is -1
        
        sequence_2.back() = last_entry_in_node;
        
        ucf_at_domain = nullptr;
    }
    
    void MoveLastEntryInNode ()
    {
        //current is disc type
        // move the last entry to -1.
        
        sequence_2.pop_back();
        ucf_at_domain = LastNodeInDomain();
        
    }
    
    
    void MoveLastEntryInNode (const LevelTwoTree & Q,
                              const LevelTwoTreeNode * const q)
    {
    
        if (q == nullptr)
        {
            MoveLastEntryInNode();
            return;
        }
        auto && move_sequence = q->LastEntry().first;
        
        if (Q.Degree (q) == DEGREE::ZERO)
        {
            MoveLastEntryInNode (move_sequence);
        }
        else
        {
            auto && new_ucf = Q.SequenceMinusValue (q);
            MoveLastEntryInNode (move_sequence, new_ucf);
        }
    }
    
    void MoveLastEntryInNode (const Level_leq_2_Tree & Q,
                              const Level_leq_2_TreeNode & q)
    {
        MoveLastEntryInNode (Q.tree_2, std::get<2> (q) );
    }
    
    
    //****************//
    // specific to 21 desc!!!//
    
    SingleSequence UCF() const
    //uniform cofinality, provided not -1
    {
        return factor.Value (ucf_at_domain);
    }
    
    bool IsContinuousType_Star (const LevelOneTree & W) const
    // is it *-W-continuous type>
    {
        if (degree == DEGREE::ONE)
            return true;
            
        if (ucf_at_domain == nullptr)
        {
            return true;
        }
        
        auto && ucf = UCF();
        
        if (W.IsTrivial() ||  ucf ==  W.SmallestEntry() )
        {
            return true;
        }
        
        if (ucf_at_domain->BKLeft() == nullptr)
        {
            return false;
        }
        
        if (IsBKPredecessor (factor.Value (ucf_at_domain->BKLeft() ), factor.Value (ucf_at_domain), W) )
        {
            return true;
        }
        return false;
    }
    
    
    bool IsDiscontinuousType_Star (const LevelOneTree & W) const
    // is it *-W-disc type?>
    {
        return ! (IsContinuousType_Star (W) );
    }
    
    // ************finished specifec to 21-desc**************//
    
    //**************************
    
    //************starting specific to 221-desc******************//
    
    
    A UCF_As21Desc() const
    //uniform cofinality, regarded as a (*, Q \otimes W) desc, provided not -1
    {
        return factor.Value (ucf_at_domain);
    }
    
    bool IsContinuousType (const LevelOneTree & W) const
    {
        if (degree == DEGREE::ONE)
        {
            return false;
        }
        if (IsDiscontinuousTypeAtDomain() )
        {
            return false;
        }
        return UCF_As21Desc().IsContinuousType_Star (W);
    }
    
    bool IsDiscontinuousType (const LevelOneTree & W) const
    {
        return ! IsContinuousType (W);
    }
    
    bool IsContinuousType_Star_As21Desc (const Level_leq_2_Tree & Q,
                                         const LevelOneTree & W) const
    {
        // is it *-continuous type as a (*, Q\otimes W)--desc?
        
        if (degree == DEGREE::ONE)
            return true;
        if (ucf_at_domain == nullptr)
        {
            return true;
        }
        A ucf_21_desc_left = UCF_As21Desc();
        
        MoveToBKLeft (ucf_21_desc_left, Q, W);
        
        if (ucf_21_desc_left.state == STATE::INVALID)
        {
            return true;
        }
        
        if (ucf_at_domain->BKLeft() == nullptr)
        {
            return false;
        }
        
        auto && ucf_21_desc_to_compare = factor.Value (ucf_at_domain->BKLeft() );
        
        if (ucf_21_desc_left == ucf_21_desc_to_compare)
        {
            return true;
        }
        return false;
        
    }
    bool IsDiscontinuousType_Star_As21Desc (const Level_leq_2_Tree & Q,
                                            const LevelOneTree & W) const
    {
        return ! (IsContinuousType_Star_As21Desc (Q, W) );
    }
    
};





// provided these nodes are alraedy in the tree or domain of tree!!
LevelOneTreeNode* BKLeft (const SingleSequence & s, const LevelOneTree & W)
{
    return W.MyNode (s)->BKLeft();
}

LevelTwoTreeNode* BKLeft (const DoubleSequence & s, const LevelTwoTree & W)
{
    return W.MyNodeInDomain (s)->BKLeft();
}

/*
LevelTwoTreeNode* Left(const DoubleSequence & s, const LevelTwoTree & W)
{
    return W.MyNodeInDomain(s)->Left();
}*/


// move D to BKleft desc of (Q,W)
// D must start as valid
//
void MoveToBKLeft (Level_21_Desc & D,
                   const Level_leq_2_Tree & Q,
                   const LevelOneTree & W)
{
    const auto & Q1 = Q.tree_1;
    const auto & Q2 = Q.tree_2;
    
    // deal with the degree 1 case first
    //
    if (D.Degree() == DEGREE::ONE)
    {
        auto && left = BKLeft (D.GetSequence_1(), Q1);
        if (left != nullptr)
        {
            D.sequence_1 = Q1.EntireEntry (left);
            return;
        }
        D.state = STATE::INVALID;
        return;
    }
    
    // now D degree 2
    //
    auto && node = Q2.MyNodeInDomain (D.GetSequence_2() );
    
    if (D.IsDiscontinuousType_Star (W) )
    {
        //end extend output
        
        auto && ucf = D.UCF();
        auto && new_in_image = BKLeft (ucf, W);
        // the biggest element before ucf of D
        // it must be put on the next entry
        
        D.DiscontinuousTrim();
        D.Extend (Q2,
                  node->LastChild(),
                  W.EntireEntry (new_in_image) );
        return;
    }
    else
    {
        D.DiscontinuousTrim();
        
        //cannot extend D
        if (D.IsConstant() )
        {
            // D constant , so W must be trivial
            if (Q1.IsNonTrivial() )
            {
                //if Q1 trivial, the greatest of Q1 is the left
                D = Level_21_Desc (Q1.EntireEntry (Q1.Root()->BKLeft() ) ) ;
                return;
            }
            else
            {
                // if Q1 is also trivial, no more
                D.state = STATE::INVALID;
                return;
            }
        }
//        else
//
//            if (D.IsConstant() )
//            {
//                //if D- is constant,
//                // D must be (-1,min(W))
//                if (Q1.IsNonTrivial() )
//                {
//                    // Q1 is non trivial
//                    // assign the biggest
//                    D.reset ( (new Level_21_Desc (Q1.EntireEntry (Q1.Root()->BKLeft() ) ) ) );
//                    return;
//                }
//                else
//                {
//                    // Q1 is trivial, no more
//                    D.reset ( nullptr);
//                    return;
//                }
//
//            }
//
// ***********deletet because automatic
//
        else
        {
            // move the last bit in Q2
            
            D.MoveLastEntryInNode (Q2,
                                   node->Left()
                                  );
            return;
        }
    }
}



// given D, a (Q,W)-desc,
//          THAT CAN BE CONTINUED TO a (Q,W')-desc,
//          W' is the completion of (W,w),
// D' , either nullptr or a (Q,W')-desc whose restriction to (Q,W) is D,
// move D' to the left of D' whose restriction is still D
// W' is the completion of (W,w), w is the hanging node in W'\W
//
void MoveToLeft (const Level_21_Desc & D,
                 Level_21_Desc & D_prime,
                 const Level_leq_2_Tree & Q,
                 //               const LevelOneTree & W,
                 const LevelOneTree & W_prime,
                 const LevelOneTreeNode * w)
{

    auto && w_sequence = W_prime.EntireEntry (w);
    /*   if (ucf_at_domain == nullptr)
       {
           return nullptr;
       }
       if (sigma.Value (ucf_at_domain) != W_prime.EntireEntry (w->Parent()))
       {
           return nullptr;
       }
    // ucf of D must be non -1, and equal to w, to be able to extend
    */
    
    if (D_prime.state  == STATE::INVALID)
    {
        D_prime = D ;
        //copy D
        D_prime.DiscontinuousTrim();
        // trim it to discontinuous
        
        // now add w and the rightmost node in Q
        const auto & Q2 = Q.tree_2;
        auto && critical_node = Q2.MyNodeInDomain (D_prime.GetSequence_2() );
        
        D_prime.Extend (Q2,
                        critical_node->LastChild(),
                        std::move (w_sequence) );
        return;
        
        /*     return BKLeft(D, Q, W_prime);*/
    }
    // the first on the left of D is the (Q,W')-left
    
    
    
    /*
        auto output = BKLeft (D_prime, Q, W_prime);
        auto compared = BKLeft (D, Q, W);
        if (output == nullptr)
        {
            return nullptr;
        }
        if (compared == nullptr)
        {
            return output;
        }
        if (*output == *compared)
        {
            return nullptr;
        }
        return output;
        */
    // *********************
    // the above chunk is replaced by a better algorithm
    // ****************************
    
    auto && length_to_compare = D.GetSequence_2().size();
    auto && length = D_prime.GetSequence_2().size();
    if (length > length_to_compare)
    {
        // if D' is effectively longer than D, no probelem
        //      that its BK left is still valeid
        MoveToBKLeft (D_prime, Q, W_prime);
        return;
    }
    
    // now D' and D are effectivel the same length
    // this means D' is continuous at domain, ending with (w, -1)
    // so impossible to move
    
    D_prime.state = STATE::INVALID;
    return;
}


Level_121_Factor TensorProduct (const Level_leq_2_Tree & Q, const LevelOneTree & W)
{

    Level_121_Factor output;
    
    Level_21_Desc D; //initialize to the constant desc
    
    MoveToBKLeft (D, Q, W);
    
    auto current = output.Root();
    
    while (D.state == STATE::VALID)
    {
        current = output.AddChildBelow (current, current->NumberOfChildren() , D);
        MoveToBKLeft (D, Q, W);
    }
    
    Flatten (output);
    
    return output;
    
}



//given C , a (T,Q,W)-desc
//given C', either nullptr or a (T,Q,W')-desc whose restriction to (T,Q,W) is C
// where W' is a one-node extension of W with hanging node w in W'\W
//
// outputs the candidate of the left of C' whose restriction to (T,Q,W) is still C
//
//
//  REMARK: C is a (T,Q,(W,w-))-desc
//
// ****** candidate means: good at transition point***********
//
void MoveToLeftCandidate (const Level_221_Desc & C,
                          Level_221_Desc & C_prime,
                          const Level_leq_2_Tree &           T,
                          const Level_leq_2_Tree &           Q,
                          //                      const LevelOneTree & W,
                          const LevelOneTree & W_prime,
                          const LevelOneTreeNode * w)
{
    const auto & T2 = T.tree_2;
    
    if (C_prime.state == STATE::INVALID)
    {
    
        C_prime = C;
        C_prime.DiscontinuousTrim();
        //
        
        //create a valid candidate desc, well-behaved at transition point
        
        auto && critical_node = C.UCFAtDomain();
        auto && factor = C.GetFactor();
        auto && critical_21_desc = factor.Value (critical_node);
        // the desc to be decreased
        
        auto && node_in_T2 = T2.MyNodeInDomain (C.GetSequence_2() );
        
        Level_21_Desc critical_left (STATE::INVALID);
        
        MoveToLeft (critical_21_desc, critical_left, Q,  W_prime, w);
        //the next smaller desc
        /*
                if (critical_left == nullptr)
                {
                    C_prime.reset ( nullptr);
                    return;
                }*/
        // automatic, for future ease of 332 factor computation
        
        C_prime.Extend (T2,
                        node_in_T2->LastChild(),
                        std::move (critical_left) );
        return;
    }
    
    
    // now C'is not nullptr. it is a potential extension, validated at transition point
    
    auto && node_in_T2 = T2.MyNodeInDomain (C_prime.GetSequence_2() );
    
    auto && effective_length = C_prime.GetSequence_2().size();
    
    
    // later check if it properly extend the core part of C
    auto && effective_length_to_compare = C.GetSequence_2().size();
    
    if (C_prime.IsDiscontinuousType_Star_As21Desc (Q, W_prime) )
    {
        //C'_effective part can be end extended as (Q,W')-desc
        
        Level_21_Desc critical_21_desc = C_prime.UCF_As21Desc();
        
        //    unique_ptr<Level_21_Desc> critical_left;
        
        if (effective_length > effective_length_to_compare)
        {
            MoveToBKLeft (critical_21_desc, Q, W_prime);
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
            auto && bound_in_C =  C.UCF_As21Desc();
            MoveToLeft (bound_in_C, critical_21_desc, Q,  W_prime, w);
            
            //found the good transition
        }
        
        
        if (critical_21_desc.state == STATE::INVALID)
        {
            //squeezed out
            // no more
            C_prime.state = STATE::INVALID;
            return;
        }
        // now critical_left is the extention of C'_effective part,
        // need to find the node
        
        C_prime.DiscontinuousTrim();
        C_prime.Extend (T2,
                        node_in_T2->LastChild(),
                        std::move (critical_21_desc) );
        return;
    }
    else
    {
        //cannot extend C_effective_part
        
        if (effective_length == effective_length_to_compare)
        {
            // C' is C_effective_part exteded by (D,-1), D not extendable
            C_prime.state = STATE::INVALID;
            return;
            // get squeezed out
        }
        
        //otherwise,
        // if node_in_T2 is the root, get sqeezed out
        // if not, move to the left
        
        if (node_in_T2->IsEmpty() )
        {
            // it is (least desc, -1)
            C_prime.state = STATE::INVALID;
            return ;
            // squezed out
        }
        
        //start moving
        
        C_prime.DiscontinuousTrim();
        C_prime.MoveLastEntryInNode (T2,
                                     node_in_T2->Left() );
        return;
    }
}



//given C, a (T,Q,(W,w-)-desc
// W' is the completion of (W,w), w is the hanging node in W'\w
// C' is a candidate (T,Q,W')-desc, produced by the MoveToLeftCandidate function, good at transition
//verify if C' is a (T,Q,W')-desc
//
bool Validate (const Level_221_Desc &     C,
               const Level_221_Desc &     C_prime,
               const Level_leq_2_Tree &  T,
               const Level_leq_2_Tree &  Q,
               const LevelOneTree & W_prime,
               const LevelOneTreeNode * w)
{

    if (C_prime.state == STATE::INVALID)
    {
        return false;
    }
    
    
    if (C_prime.IsDiscontinuousTypeAtDomain() )
    {
        return true;
    }
    
    auto && effective_length = C_prime.GetSequence_2().size();
    
    auto && effective_length_to_compare = C.GetSequence_2().size();
    
    if (effective_length > effective_length_to_compare)
    {
        return true;
    }
    
    auto && last_node_in_C_prime = C_prime.LastNodeInDomain();
    auto && critical_desc = C_prime.GetFactor().Value (last_node_in_C_prime);
    auto && critical_factor = critical_desc.GetFactor();
    
    //now C' is C_effective_part plus (D, -1)
    // we need to make sure of the well-behavior of D
    
    if (critical_desc.IsDiscontinuousTypeAtDomain() )
        return true;
        
        
    auto && last_node = critical_desc.LastNodeInDomain();
    auto && last_value = critical_factor.Value (last_node);
    if (last_value != W_prime.EntireEntry (w) )
    {
        return true;
    }
    
    //otherwise, last value is w
    //then
    return false;
}

//given C , a (T,Q,(W,w)-desc,
//given C', a (T,Q,W')-desc whose restriction to (T,Q,W) is C
// where W' is a one-node extension of W by adding w in W'\W
// outputs the left of C' whose restriction to (T,Q,W) is still C
//
void MoveToLeft (const Level_221_Desc &     C,
                 Level_221_Desc &     C_prime,
                 const Level_leq_2_Tree &  T,
                 const Level_leq_2_Tree &  Q,
                 //              const LevelOneTree &      W,
                 const LevelOneTree & W_prime,
                 const LevelOneTreeNode * w)
{
    MoveToLeftCandidate (C, C_prime, T, Q,  W_prime, w);
    
    do
    {
        if (C_prime.state == STATE::INVALID)
        {
            return;
        }
        //hit the wall. no more
        
        if (Validate (C, C_prime, T, Q,  W_prime, w) )
        {
            return;
            //validated, retun the current desc
        }
        
        // if not validated, continue searching
        
        MoveToLeftCandidate (C, C_prime, T, Q,  W_prime, w);
        //move left
    }
    while (true);
}

// C is a (*,*,(W,w))-desc
// get the w such that C is a (*,*,(W,-1))-desc or (*,*,(W,w+))-desc,
// w is the ucf of the base
//
LevelOneTreeNode * BaseUCF (const Level_221_Desc & C,
                            const LevelOneTree & W)
{

    if (C.ucf_at_domain == nullptr)
    {
        return nullptr;
    }
    
    auto && critical_desc = C.UCF_As21Desc();
    
    if (critical_desc.ucf_at_domain == nullptr)
    {
        return nullptr;
    }
    
    auto && critical_desc_ucf = critical_desc.UCF_As21Desc();
    
    return W.MyNode (critical_desc_ucf);
}





class Level_222_Factor
{

public:

    Level_leq_2_Tree domain;
    Level_121_Factor factor_1;
    FuncTree<SingleSequence, Level_221_Desc> factor_2;
    
    
public:

    string to_string (const unsigned & d = 0) const
    {
        // only implemented level 2 part!!
        
        string output;
        auto i = domain.tree_2.Root()->FirstChild();
        auto j = factor_2.Root()->FirstChild();
        while (i != nullptr)
        {
            output += EmptyString (d);
            output += ::to_string (domain.tree_2.EntireEntryInDomain (i) );
            
            output += " |---> the following 221 desc:\n";
            
            output += ::to_string (j->LastEntry().second, d + indent);
            output += "\n";
            i = domain.tree_2.NextEnumerate (i);
            j = factor_2.NextEnumerate (j);
        }
        return output;
    }
    
    
    friend void swap (Level_222_Factor & f, Level_222_Factor & g)
    {
        swap (f.domain, g.domain);
        swap (f.factor_1, g.factor_1);
        swap (f.factor_2, g.factor_2);
    }
    
    Level_222_Factor() = default;
    Level_222_Factor (const Level_222_Factor & pi) = default;
    Level_222_Factor (Level_222_Factor && pi)
    {
        swap (*this, pi);
    }
    Level_222_Factor& operator= (Level_222_Factor pi)
    {
        swap (*this, pi);
        return *this;
    }
    
//   Level_222_Factor(const LevelOneFactor & pi1, const LevelTwoFactor & pi2);


    unsigned long Cardinality() const
    {
        return factor_1.Cardinality() + factor_2.Cardinality();
    }
    
    Level_222_FactorNode Root_1 () const
    {
        return Level_222_FactorNode (DEGREE::ONE,
                                     domain.tree_1.Root(),
                                     factor_1.Root(),
                                     nullptr,
                                     nullptr);
    }
    Level_222_FactorNode Root_2 () const
    {
        return Level_222_FactorNode (DEGREE::TWO,
                                     nullptr,
                                     nullptr,
                                     domain.tree_2.Root(),
                                     factor_2.Root() );
    }
    
    
    bool operator == (const Level_222_Factor & pi) const
    {
        return (domain == pi.domain && factor_1 == pi.factor_1 && factor_2 == pi.factor_2);
    }
    bool operator != (const Level_222_Factor & pi) const
    {
        return ! (*this == pi);
    }
    
    const Level_leq_2_Tree &   Domain() const
    {
        return domain;
    }
    const Level_121_Factor &   Factor_1() const
    {
        return factor_1;
    }
    const FuncTree<SingleSequence, Level_221_Desc>  &  Factor_2() const
    {
        return factor_2;
    }
    
    leq_2_Sequence EntireEntryInDomain (const Level_222_FactorNode & s) const
    {
        if (Degree (s) == DEGREE::ZERO)
        {
            return zero_leq_2_Sequence;
        }
        if (Degree (s) == DEGREE::ONE)
        {
            return leq_2_Sequence (
                       DEGREE::ONE,
                       domain.tree_1.EntireEntry (NodeInTree_1 (s) ),
                       DoubleSequence() );
        }
        else
        {
            return leq_2_Sequence (
                       DEGREE::TWO,
                       SingleSequence(),
                       domain.tree_2.EntireEntryInDomain (NodeInTree_2 (s) ) );
        }
    }
    
    
    Level_222_FactorNode MyNodeInDomain (const leq_2_Sequence & s) const
    {
        if (std::get<0> (s) == DEGREE::ZERO)
        {
            return zeroLevel_leq_2_FactorNode;
        }
        
        if (std::get<0> (s) == DEGREE::ONE)
        {
            return MyNodeInDomain (std::get<1> (s) );
        }
        else
            return MyNodeInDomain (std::get<2> (s) );
    }
    
private:
    Level_222_FactorNode MyNodeInDomain (const SingleSequence & s) const
    {
    
    
        return  Level_222_FactorNode
                (
                    DEGREE::ONE,
                    domain.tree_1.MyNode (s),
                    factor_1.MyNodeInDomain (s),
                    nullptr,
                    nullptr)
                ;
    }
    
    Level_222_FactorNode MyNodeInDomain (const DoubleSequence & s) const
    {
        return Level_222_FactorNode
               (
                   DEGREE::TWO,
                   nullptr,
                   nullptr,
                   domain.tree_2.MyNodeInDomain (s),
                   factor_2.MyNodeInDomain (s)
               )
               ;
    }
    
public:
    // is it continuous at (s,i), viewed as a map factoing
    //      into T \otimes Q?
    //
    // where s is a node in my own tree and factor
    //
    bool IsContinuous (const Level_leq_2_Tree & T,
                       const Level_leq_2_Tree & Q,
                       const Level_222_FactorNode & s,
                       const DIRECTION & i) const
    {
        if (Degree (s) == DEGREE::ZERO)
        {
            return true;
        }
        
        if (Degree (s) == DEGREE::ONE)
        {
            auto && desc = factor_1.Value (NodeInFactor_1 (s) );
            
            // copy the critical 21-desc, and move left
            auto desc_left = desc;
            MoveToBKLeft (desc_left, T, Q.tree_1);
            
            if (desc_left.state == STATE::INVALID)
            {
                // if the image is leftmost,
                //      it is alraady leftmost
                return true;
            }
            
            // now the left of image exists
            auto && left_at_domain = NodeInFactor_1 (s)->BKLeft();
            if ( left_at_domain == nullptr)
            {
                // if s is leftmost, not continuous
                return false;
            }
            
            // now both left exists
            return desc_left == factor_1.Value (left_at_domain);
        }
        
        // now s has degree 2
        
        auto && node_in_factor_2 = NodeInFactor_2 (s);
        auto && node_in_tree_2 = NodeInTree_2 (s);
        
        // by our assumption, if s is root then going down
        
        if (i == DIRECTION::LEFT)
        {
            // the ucf is going left, s must be not root
            auto && desc = factor_2.Value (node_in_factor_2 );
            auto && desc_parent = factor_2.Value (node_in_factor_2->Parent() );
            // the image 221 desc and its parent
            
            auto && Ww = domain.tree_2.Value (node_in_tree_2->Parent() );
            // the partial tree at the parent  of s
            // from this, we compute W and W_plus
            
            //         auto && W = Ww.Tree();
            
            auto && Ww_plus = Ww.CompletionWithNode ();
            
            auto && W_plus = Ww_plus.first;
            auto && w = Ww_plus.second;
            
            auto left = desc;
            MoveToLeft (desc_parent,
                        left,
                        T,
                        Q,
                        W_plus,
                        w
                       );
            // move to the left ,  having same parent and same ucf
            
            if (left.state == STATE::INVALID)
            {
                // if no left in the image, cont!
                return true;
            }
            
            // now the left of image 221 desc exists
            auto && left_at_domain = NodeInFactor_2 (s)->Left();
            if ( left_at_domain == nullptr)
            {
                // if s is leftmost, not continuous
                return false;
            }
            
            // now both left exists
            return left == factor_2.Value (left_at_domain);
        }
        else
        {
            // the ucf is going down
            auto && desc = factor_2.Value (NodeInFactor_2 (s) );
            
            Level_221_Desc left (STATE::INVALID);
            auto && Ww = domain.tree_2.Value (NodeInTree_2 (s) );
            // the partial tree at s
            // from this, we compute W and W_plus
            //        auto && W = Ww.Tree();
            
            auto && Ww_plus = Ww.CompletionWithNode ();
            
            auto && W_plus = Ww_plus.first;
            auto && w = Ww_plus.second;
            
            MoveToLeft (desc, left, T, Q,  W_plus, w);
            
            if (left.state == STATE::INVALID)
            {
                // if no left in the image, cont!
                return true;
            }
            
            // now the left of image 221 desc exists
            auto && left_at_domain = NodeInFactor_2 (s)->LastChild();
            if ( left_at_domain == nullptr)
            {
                // if s is leftmost, not continuous
                return false;
            }
            
            // now both left exists
            return left == factor_2.Value (left_at_domain);
        }
    }
    
    
    Level_222_FactorNode Remove (const Level_222_FactorNode & s);
    
    
    template <typename A>
    Level_222_FactorNode Add (const Level_222_FactorNode & s,
                              A && y)
    // s is degree 1,
    // add below s, with value y, as a 21-desc
    {
        auto && new_node_in_tree = domain.tree_1.AddChildBelow (NodeInTree_1 (s) );
        auto && new_node_in_factor = AddChildBelow (factor_1, NodeInFactor_1 (s), std::forward<A> (y) );
        return Level_222_FactorNode (DEGREE::ONE,
                                     new_node_in_tree,
                                     new_node_in_factor,
                                     nullptr,
                                     nullptr);
    }
    
    template <typename A>
    Level_222_FactorNode Add (const Level_222_FactorNode & s,
                              const DIRECTION & i,
                              PartialLevelOneTree && P,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    {
        auto && new_node_in_tree = ::Add (domain.tree_2,  NodeInTree_2 (s), i, std::move (P) );
        auto && new_node_in_factor = ::Add (factor_2, NodeInFactor_2 (s), i, std::forward<A> (y) );
        return Level_222_FactorNode (DEGREE::TWO,
                                     nullptr,
                                     nullptr,
                                     new_node_in_tree,
                                     new_node_in_factor
                                    );
    }
    
    template <typename A>
    Level_222_FactorNode Add (const Level_222_FactorNode & s,
                              const DIRECTION & i,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    // the partial tree to extend has degree 0 at the extre node
    {
        auto && N = domain.tree_2.CreateFinalTreeWithNodeFromUCF (NodeInTree_2 (s) , i);
        auto && P = PartialLevelOneTree (std::move (N).first);
        return Add (s, i, std::move (P), std::forward<A> (y) );
    }
    
    template <typename A>
    Level_222_FactorNode Add (const Level_222_FactorNode & s,
                              const DIRECTION & i,
                              const SingleSequence & s1,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    // the partial tree to extend has degree 1 at the extre node
    // with ucf s1
    {
        auto && N = domain.tree_2.CreateFinalTreeWithNodeFromUCF ( NodeInTree_2 (s), i );
        auto && P = PartialLevelOneTree (std::move (N).first, s1);
        return Add (s, i, std::move (P), std::forward<A> (y) );
    }
    
//=====================================

    template <typename A>
    Level_222_FactorNode Add (const leq_2_Sequence & s,
                              A && y)
    // s is degree 1,
    // add below s, with value y, as a 21-desc
    {
        return Add (MyNodeInDomain (s), std::forward<A> (y) );
    }
    
    template <typename A>
    Level_222_FactorNode Add (const leq_2_Sequence & s,
                              const DIRECTION & i,
                              PartialLevelOneTree && P,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    {
        return Add (MyNodeInDomain (s), i, P, std::forward<A> (y) );
    }
    
    template <typename A>
    Level_222_FactorNode Add (const leq_2_Sequence & s,
                              const DIRECTION & i,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    // the partial tree to extend has degree 0 at the extre node
    {
        return Add (MyNodeInDomain (s), i, std::forward<A> (y) );
    }
    
    template <typename A>
    Level_222_FactorNode Add (const leq_2_Sequence & s,
                              const DIRECTION & i,
                              const SingleSequence & s1,
                              A && y)
    // s is degree 2,
    // add below s, with value y, as a 221-desc
    // the partial tree to extend has degree 1 at the extre node
    // with ucf s1
    {
        return Add (MyNodeInDomain (s), i, s1, std::forward<A> (y) );
    }
    
    
    const Level_21_Desc & Value_1 (const Level_222_FactorNode & s) const
    {
        return Factor_1().Value (NodeInFactor_1 (s) );
    }
    
    const Level_221_Desc & Value_2 (const Level_222_FactorNode & s) const
    {
        return Factor_2().Value (NodeInFactor_2 (s) );
    }
    
    
    
    // n_factor is a node is the (X,T,Q)-factor map
    // the 221-desc in n is a (T,Q,W)-Desc
    // create one-node-in-W extensions of W,
    // and put them under n
    //
    // move both pointers to last children
    // if not , move to nullptr
    //
    void
    CreateChildren (
        LevelTwoTreeNode * & n_tree,
        FuncTreeNode<SingleSequence, Level_221_Desc> * & n_factor,
        const Level_leq_2_Tree &    T,
        const Level_leq_2_Tree &    Q)
    {
    
        auto temp_factor = n_factor;
        auto temp_tree = n_tree;
        
        auto && C = factor_2.Value (n_factor);
        // the 221-desc in n
        
        auto & X = domain;
        auto & X2 = X.tree_2;
        
        auto && w_node = X2.Value (n_tree).NodeMinusInTree();
        
        if (w_node == nullptr)
        {
            // the node in X is degree 0,
            // impossible to extend
            //
            n_tree = nullptr;
            n_factor = nullptr;
            return;
        }
        
        //     auto && w_entry = W.EntireEntry (w_node);
        
        auto && Ww_prime = X2.CreateFinalTreeWithNodeFromUCF (n_tree,
                           DIRECTION::DOWN);
                           
                           
        auto && W_prime = Ww_prime.first;
        
        auto && w = Ww_prime.second;
        
        Level_221_Desc prev_desc (STATE::INVALID);
        
        MoveToLeft (C, prev_desc, T, Q,  W_prime, w);
        // try to build a child
        
        if (prev_desc.state == STATE::INVALID)
        {
            // if unsuccessful, no child
            n_tree = nullptr;
            n_factor = nullptr;
            return;
        }
        
        // found the child, add it into both X2 and factor_2 according to
        // the new ucf
        
        // add into factor2
        
        auto && current_in_factor = AddChildBelow<Level_221_Desc>
                                    (factor_2, n_factor, prev_desc);
                                    
                                    
        // starting to add into X2
        LevelOneTreeNode * new_ucf = BaseUCF (prev_desc, W_prime) ;
        LevelTwoTreeNode * current_in_X2;
        if (new_ucf == nullptr)
        {
            // the new node in X2 is degree 0
            current_in_X2 = AddChildBelow<PartialLevelOneTree>
                            (X2, n_tree, PartialLevelOneTree (W_prime) );
        }
        else
        {
            auto && new_ucf_entry = W_prime.EntireEntry (new_ucf);
            // the new node in X2 is degree 1
            current_in_X2 = AddChildBelow<PartialLevelOneTree>
                            (X2, n_tree, PartialLevelOneTree (W_prime, new_ucf_entry) );
        }
        // find new children, add to the left
        do
        {
            MoveToLeft (C, prev_desc, T, Q,  W_prime, w);
            if (prev_desc.state == STATE::INVALID)
            {
                //reached the end, break,
                break;
            }
            
            // add into factor2
            current_in_factor = AddSiblingLeft<Level_221_Desc>
                                (factor_2, current_in_factor, prev_desc);
            // COPY prev_desc into factor_2!!!
            // DON'T MOVE, as prev_desc will be used later
            
            // starting to add into X2
            new_ucf = BaseUCF (prev_desc, W_prime) ;
            if (new_ucf == nullptr)
            {
                // the new node in X2 is degree 0
                current_in_X2 = AddSiblingLeft<PartialLevelOneTree>
                                (X2, current_in_X2, PartialLevelOneTree (W_prime) );
            }
            else
            {
                auto && new_ucf_entry = W_prime.EntireEntry (new_ucf);
                
                // the new node in X2 is degree 1
                current_in_X2 = AddSiblingLeft<PartialLevelOneTree>
                                (X2, current_in_X2, PartialLevelOneTree (W_prime, new_ucf_entry) );
                                
            }
        }
        while (true);
        
        n_factor = temp_factor->LastChild();
        n_tree = temp_tree->LastChild();
        
        return;
    }
};

// applies to degr 2 only
Level_222_FactorNode Parent (const Level_222_FactorNode & s)
{
    return Level_222_FactorNode (DEGREE::TWO,
                                 nullptr,
                                 nullptr,
                                 NodeInTree_2 (s)->Parent(),
                                 NodeInFactor_2 (s)->Parent() );
}





Level_222_Factor TensorProduct (const Level_leq_2_Tree & T, const Level_leq_2_Tree & Q)
{
    Level_222_Factor pi;
    pi.factor_1 = TensorProduct (T, Q.tree_1);
    pi.domain.tree_1 = pi.factor_1.Domain();
    
    // the level_1 component is just 21 tensor product
    
    
    auto current_factor = pi.factor_2.Root();
    auto current_tree = pi.domain.tree_2.Root();
    
    
    auto temp_factor = current_factor;
    auto temp_tree = current_tree;
    
    unsigned shiwan = 1;
    
    while (true)
    {
    
        if (pi.Cardinality() > shiwan * 100000)
        {
            cout << pi.Cardinality() << " added!" << endl;
            cout << "continue?" << endl;
            cin.get();
            shiwan = pi.Cardinality() / 100000 + 1;
        }
        
        pi.CreateChildren (temp_tree, temp_factor, T, Q);
        
        
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
            // output!!!
            Flatten (pi.domain.tree_1);
            Flatten (pi.domain.tree_2);
            Flatten (pi.factor_1);
            Flatten (pi.factor_2);
            return pi;
        }
        current_factor = current_factor->Left();
        current_tree = current_tree->Left();
        
        temp_factor = current_factor;
        temp_tree = current_tree;
        
    }
}


unsigned long DynamicTensorProduct (const Level_leq_2_Tree & T,
                                    const Level_leq_2_Tree & Q,
                                    ofstream  & myfile)
{
    if (myfile.is_open() )
    {
        int depth = 0;
        
        myfile << "(0)" << endl;
        
        Level_222_Factor pi;
        pi.factor_1 = TensorProduct (T, Q.tree_1);
        unsigned long output = pi.factor_1.Cardinality();
        
        unsigned long qian = 1;
        unsigned long ji = 1;
        
        pi.domain.tree_1 = pi.factor_1.Domain();
        
        // the level_1 component is just 21 tensor product
        
        
        auto current_factor = pi.factor_2.Root();
        auto current_tree = pi.domain.tree_2.Root();
        
        
        auto temp_factor = current_factor;
        auto temp_tree = current_tree;
        
        while (true)
        {
            if (output > qian * 1000)
            {
                cout << "\r " << output << " nodes computed!          " << std::flush;
                qian += 1;
            }
            
            
            pi.CreateChildren (temp_tree, temp_factor, T, Q);
            
            
            
            if (temp_factor != nullptr)
            
            {
                current_factor = temp_factor;
                current_tree = temp_tree;
                output += current_factor->Parent()->NumberOfChildren();
                
                ++depth;
                
                
                vector<LevelTwoTreeNode*> history;
                auto record = current_tree->Parent();
                for (int a = depth - 1; a > 0; --a)
                {
                    history.emplace_back (record);
                    record = record -> Parent();
                }
                
                
                
                if (depth >= 2)
                {
                
                    for (int a = depth - 2;  a >= 0 ; --a)
                    {
                        if (history[a]->IsLastBitLeftMost() )
                            myfile << " \t";
                        else
                            myfile << "|\t";
                    }
                }
                myfile << "+" << string (interval, '-');
                myfile << to_string (pi.domain.tree_2.CreateHangingSequence (current_tree) ) << endl;
                
                continue;
            }
            
            
            while (current_factor != nullptr &&
                    current_factor->Left() == nullptr)
            {
                current_factor = current_factor->Parent();
                current_tree = current_tree->Parent();
                
                --depth;
                
                if (current_factor != nullptr && current_factor->IsNonEmpty() )
                {
                
                    pi.domain.tree_2.SpecialRemove (current_tree->FirstChild() );
                    pi.factor_2.SpecialRemove (current_factor->LastChild() );
                }
                
            }
            if (current_factor == nullptr)
            {
                cout << std::flush << endl;
                return output;
            }
            
            temp_factor = current_factor;
            temp_tree = current_tree;
            
            
            current_factor = current_factor->Left();
            current_tree = current_tree->Left();
            
            pi.domain.tree_2.SpecialRemove (temp_tree);
            pi.factor_2.SpecialRemove (temp_factor);
            
            temp_factor = current_factor;
            temp_tree = current_tree;
            
            
            vector<LevelTwoTreeNode*> history = vector<LevelTwoTreeNode*> ();
            auto record = current_tree->Parent();
            for (int a = depth - 1; a > 0; --a)
            {
                history.emplace_back (record);
                record = record -> Parent();
            }
            
            
            
            if (depth >= 2)
            {
            
                for (int a = depth - 2; a >= 0 ; --a)
                {
                    if (history[a]->IsLastBitLeftMost() )
                        myfile << " \t";
                    else
                        myfile << "|\t";
                }
            }
            myfile << "+" << string (interval, '-');
            myfile << to_string (pi.domain.tree_2.CreateHangingSequence (current_tree) ) << endl;
            
        }
        
        return output;
    }
    
    else
    {
    
        int depth = 0;
        
        
        Level_222_Factor pi;
        pi.factor_1 = TensorProduct (T, Q.tree_1);
        unsigned long output = pi.factor_1.Cardinality();
        
        unsigned long qian = 1;
        unsigned long ji = 1;
        
        pi.domain.tree_1 = pi.factor_1.Domain();
        
        // the level_1 component is just 21 tensor product
        
        
        auto current_factor = pi.factor_2.Root();
        auto current_tree = pi.domain.tree_2.Root();
        
        
        auto temp_factor = current_factor;
        auto temp_tree = current_tree;
        
        while (true)
        {
            if (output > qian * 1000)
            {
                cout << "\r " << output << " nodes computed!          " << std::flush;
                qian += 1;
            }
            
            
            pi.CreateChildren (temp_tree, temp_factor, T, Q);
            
            if (temp_factor != nullptr)
            
            {
                current_factor = temp_factor;
                current_tree = temp_tree;
                output += current_factor->Parent()->NumberOfChildren();
                
                ++depth;
                
                vector<LevelTwoTreeNode*> history;
                auto record = current_tree->Parent();
                for (int a = depth - 1; a > 0; --a)
                {
                    history.emplace_back (record);
                    record = record -> Parent();
                }
                
                if (depth >= 2)
                {
                
                    for (int a = depth - 2;  a >= 0 ; --a)
                    {
                        if (history[a]->IsLastBitLeftMost() )
                            myfile << " \t";
                        else
                            myfile << "|\t";
                    }
                }
                
                continue;
            }
            
            
            while (current_factor != nullptr &&
                    current_factor->Left() == nullptr)
            {
                current_factor = current_factor->Parent();
                current_tree = current_tree->Parent();
                
                --depth;
                
                if (current_factor != nullptr && current_factor->IsNonEmpty() )
                {
                
                    pi.domain.tree_2.SpecialRemove (current_tree->FirstChild() );
                    pi.factor_2.SpecialRemove (current_factor->LastChild() );
                }
                
            }
            if (current_factor == nullptr)
            {
                return output;
            }
            
            temp_factor = current_factor;
            temp_tree = current_tree;
            
            
            current_factor = current_factor->Left();
            current_tree = current_tree->Left();
            
            pi.domain.tree_2.SpecialRemove (temp_tree);
            pi.factor_2.SpecialRemove (temp_factor);
            
            temp_factor = current_factor;
            temp_tree = current_tree;
            
            
            vector<LevelTwoTreeNode*> history = vector<LevelTwoTreeNode*> ();
            auto record = current_tree->Parent();
            for (int a = depth - 1; a > 0; --a)
            {
                history.emplace_back (record);
                record = record -> Parent();
            }
            
            if (depth >= 2)
            {
            
                for (int a = depth - 2; a >= 0 ; --a)
                {
                    if (history[a]->IsLastBitLeftMost() )
                        myfile << " \t";
                    else
                        myfile << "|\t";
                }
            }
        }
        return output;
    }
}



string to_string (const vector<tuple<int, SingleSequence, Level_21_Desc>> & r)
{
    string output;
    for (auto && i : r)
    {
        if (std::get<0> (i) == 2)
        {
            output += to_string (std::get<2> (i) );
        }
        else if (std::get<0> (i) == 1)
        {
            output += to_string (std::get<1> (i) );
        }
        else
        {
            output += "-1";
        }
    }
    return output;
}



class PartialLevel_leq_2_Tree
{

public:

    string to_string (const unsigned & d = 0) const
    {
        string output = ::to_string (tree, d);
        output += "\n";
        output += EmptyString (d);
        output += "Hanging:";
        output += ::to_string (CreateHangingSequence() );
        return output;
    }
    
    Level_leq_2_Tree    tree;
    
    Level_leq_2_TreeNode node_minus;
    DIRECTION           direction;
    
    FinalTreeWithNode   final_tree_with_node;
    
    //
    // degree can be ZERO ONE TWO
    // node_minus is the sequence in the level <=2 tree
    // the actual node is the extension of node_minus
    //          (extension on the double , or last of the double,
    //             or extension on the single)
    //
    // the final level-1 tree with node is defined when degree 2
    //
    // NOTE: the special case when ucf_node = (2,root) and ucf_direction = left
    //          in the paper is replaced here by
    //                              ucf_node = (1,root) and ucf_direction = down
    //          as the new node is indeed downwards of 1root,
    //      for convenience
    
public:
    ~PartialLevel_leq_2_Tree () = default;
    
    PartialLevel_leq_2_Tree (PartialLevel_leq_2_Tree&& P)
    {
        swap (*this, P);
    }
    
    friend void swap (PartialLevel_leq_2_Tree & M,
                      PartialLevel_leq_2_Tree & P)
    {
        swap (M.tree, P.tree);
        std::swap (M.direction, P.direction);
        std::swap (M.node_minus, P.node_minus);
        std::swap (M.final_tree_with_node, P.final_tree_with_node);
    }
    
    PartialLevel_leq_2_Tree& operator= (PartialLevel_leq_2_Tree P)
    {
        swap (*this, P);
        return *this;
    }
    
    PartialLevel_leq_2_Tree() :
        PartialLevel_leq_2_Tree (DEGREE::ZERO) {}
    // This is just for convenience
    // in fact, R(empty) does not have a value at all
    // take caution always
    
    
    PartialLevel_leq_2_Tree (const DEGREE & d) :
        //only defaulted by degree
        // degree can be ZEAO ONE TWO
        // deriction can be nevre left
        tree (Level_leq_2_Tree () )
    {
        if (d == DEGREE::ZERO)
        {
            node_minus = zeroLevel_leq_2_TreeNode;
            direction = DIRECTION::NA;
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        if (d == DEGREE::ONE)
        {
            node_minus = Level_leq_2_TreeNode (DEGREE::ONE,
                                               tree.tree_1.Root(),
                                               nullptr);
                                               
            direction = DIRECTION::DOWN;
            
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        if (d == DEGREE::TWO)
        {
            node_minus = Level_leq_2_TreeNode (DEGREE::TWO,
                                               nullptr,
                                               tree.tree_2.Root() );
            direction = DIRECTION::DOWN;
            final_tree_with_node = tree.tree_2.Root()->LastEntry().second.CompletionWithNode();
            // set the final level-1 tree to be of card 1,
            //    with (0) as unique element
            //              and as the hanging node from prev level
        }
    }
    
    PartialLevel_leq_2_Tree (const PartialLevel_leq_2_Tree & PP) :
        tree (PP.tree),
        direction (PP.direction)
    {
        if (std::get<0> (PP.node_minus) == DEGREE::ZERO)
        {
            node_minus = zeroLevel_leq_2_TreeNode;
        }
        else
        {
            node_minus = tree.MyNode (PP.tree.EntireEntry (PP.node_minus) );
        }
        
        if (std::get<0> (PP.node_minus) != DEGREE::TWO)
        {
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else
        {
            MakeCopy (final_tree_with_node, PP.final_tree_with_node);
        }
    }
    
    PartialLevel_leq_2_Tree (const Level_leq_2_Tree & P) :
        // construct a partial level <=2 tree
        // of degree 0
        // from a level <= 2 tree
        tree (P),
        node_minus (zeroLevel_leq_2_TreeNode ),
        direction (DIRECTION::NA),
        final_tree_with_node (LevelOneTree(), nullptr)
    {}
    PartialLevel_leq_2_Tree (Level_leq_2_Tree && P) :
        // construct a partial level <=2 tree
        // of degree 0
        // from a level <= 2 tree
        tree (std::move (P) ),
        node_minus (zeroLevel_leq_2_TreeNode),
        direction (DIRECTION::NA),
        final_tree_with_node (LevelOneTree(), nullptr)
    {}
    
    
    PartialLevel_leq_2_Tree (const Level_leq_2_Tree & P,
                             const SingleSequence & s) :
        // construct a partial level <=2 tree
        // of degree 1
        // from a level <= 2 tree
        // specify: the ucf s
        //
        tree (P),
        node_minus (Level_leq_2_TreeNode (DEGREE::ONE,
                                          tree.tree_1.MyNode (s) ,
                                          nullptr) ),
        direction (DIRECTION::DOWN),
        final_tree_with_node (LevelOneTree(), nullptr)
    {}
    PartialLevel_leq_2_Tree (Level_leq_2_Tree && P,
                             const SingleSequence & s) :
        // construct a partial level <=2 tree
        // of degree 1
        // from a level <= 2 tree
        // specify: the ucf s
        //
        tree (std::move (P) ),
        node_minus (Level_leq_2_TreeNode (DEGREE::ONE,
                                          tree.tree_1.MyNode (s) ,
                                          nullptr) ),
        direction (DIRECTION::DOWN),
        final_tree_with_node (LevelOneTree(), nullptr)
    {}
    
    PartialLevel_leq_2_Tree (const Level_leq_2_Tree & P,
                             const DoubleSequence & s,
                             const DIRECTION & i) :
        // construct a partial level <=2 tree
        // of degree 2,
        // moving down or left, depending on i
        // from a level <= 2 tree
        // specify: the direction of ucf i, the ucf s
        //
        tree (P),
        node_minus (Level_leq_2_TreeNode (DEGREE::TWO,
                                          nullptr,
                                          tree.tree_2.MyNodeInDomain (s) ) ),
        direction (i)
        
    {
        if (direction == DIRECTION::DOWN)
        {
            final_tree_with_node = std::get<2> (node_minus)->LastEntry().second.CompletionWithNode();
        }
        else
        {
            final_tree_with_node = std::get<2> (node_minus)->Parent()->LastEntry().second.CompletionWithNode();
        }
    }
    PartialLevel_leq_2_Tree ( Level_leq_2_Tree && P,
                              const DoubleSequence & s,
                              const DIRECTION & i) :
        // construct a partial level <=2 tree
        // of degree 2,
        // moving down or left, depending on i
        // from a level <= 2 tree
        // specify: the direction of ucf i, the ucf s
        //
        tree (std::move (P) ),
        node_minus (Level_leq_2_TreeNode (DEGREE::TWO,
                                          nullptr,
                                          tree.tree_2.MyNodeInDomain (s) ) ),
        direction (i)
    {
        if (direction == DIRECTION::DOWN)
        {
            final_tree_with_node = std::get<2> (node_minus)->LastEntry().second.CompletionWithNode();
        }
        else
        {
            final_tree_with_node = std::get<2> (node_minus)->Parent()->LastEntry().second.CompletionWithNode();
        }
    }
    
    /*
        // arbitrary degree
        PartialLevel_leq_2_Tree (const Level_leq_2_Tree & P,
                                 const DIRECTION & i,
                                 const leq_2_Sequence & s) :
            // construct a partial level <=2 tree
            // moving down or left, depending on i
            // from a level <= 2 tree
            // specify: the direction of ucf i, the ucf s
            //
            tree (P),
            direction (i),
            node_minus (tree.MyNode (s) )
        {
           if (direction == DIRECTION::DOWN)
            {
                final_tree_with_node = node_minus_2->LastEntry().second.CompletionWithNode();
            }
            else
            {
                final_tree_with_node = node_minus_2->Parent()->LastEntry().second.CompletionWithNode();
            }
        }
        PartialLevel_leq_2_Tree ( Level_leq_2_Tree && P,
                                  const DIRECTION & i,
                                  const DoubleSequence & s) :
            // construct a partial level <=2 tree
            // of degree 2,
            // moving down or left, depending on i
            // from a level <= 2 tree
            // specify: the direction of ucf i, the ucf s
            //
            tree (std::move (P) ),
            degree (DEGREE::TWO),
            direction (i),
            node_minus (Level_leq_2_TreeNode(DEGREE::TWO,
                                             nullptr,
                                             tree.tree_2.MyNodeInDomain (s) )
        {
           if (direction == DIRECTION::DOWN)
            {
                final_tree_with_node = node_minus_2->LastEntry().second.CompletionWithNode();
            }
            else
            {
                final_tree_with_node = node_minus_2->Parent()->LastEntry().second.CompletionWithNode();
            }
        }*/
    
    
    // degree can be 0, 1, 2
    DEGREE Degree() const
    {
        return std::get<0> (node_minus);
    }
    
    DIRECTION Direction() const
    {
        return direction;
    }
    
    // the level <=2 tree
    const Level_leq_2_Tree & Tree() const
    {
        return tree;
    }
    
    // the lvel-1 tree component
    const LevelOneTree & Tree_1() const
    {
        return tree.tree_1;
    }
    
    // the level-2 treee component
    const LevelTwoTree & Tree_2() const
    {
        return tree.tree_2;
    }
    
    // when degree 1, the node_minus in the level-1 tree
    LevelOneTreeNode * NodeMinusInTree_1 () const
    {
        return std::get<1> (node_minus);
    }
    
    // when degree 2 or 2left, the node minus in the level-2 tree
    LevelTwoTreeNode * NodeMinusInTree_2 () const
    {
        return std::get<2> (node_minus);
    }
    /*
        // when degree 1, the single sequence
        SingleSequence NodeMinusSequence_1() const
        {
            return tree.EntireEntry_1 (node_minus);
        }
    
        // when degree 2 or 2left, the double sequence
        DoubleSequence NodeMinusSequence_2() const
        {
            return tree.EntireEntryInDomain_2 ();
        }*/
    leq_2_Sequence NodeMinusSequence() const
    {
        return tree.EntireEntry (node_minus);
    }
    
    // the cardinality
    unsigned long Cardinality() const
    {
        return Tree().Cardinality() + 1;
    }
    
    //  operators
    bool operator == (const PartialLevel_leq_2_Tree & P) const = delete;
    // neveruse it anyway
    /*
    {
        if (degree != P.degree)
        {
            return false;
        }
        if (direction != P.direction)
        {
            return false;
        }
        if (tree != P.tree)
        {
            return false;
        }
        if (degree == DEGREE::ZERO)
        {
            return true;
        }
        else if (degree == DEGREE::ONE)
        {
            return node_minus_1 == *P.node_minus_1;
        }
        else
        {
            return *node_minus_2 == *P.node_minus_2;
        }
    }*/
    bool operator != (const PartialLevel_leq_2_Tree & P) const = delete;
    /*
    {
        return ! (*this == P);
    }
    */
    // whin degree 1, gives a parital <=1 tree by throwing away
    //      the level -2 part
    PartialLevelOneTree Level_leq_1_Component () const
    {
        if (Degree() == DEGREE::ZERO)
        {
            auto t1 = Tree_1();
            return PartialLevelOneTree (t1);
        }
        if (Degree() == DEGREE::ONE)
        {
            auto t1 = Tree_1();
            return PartialLevelOneTree (t1, NodeMinusInTree_1() );
        }
    }
    
    
//generates a vector of completions
// of course, empty vector if degree 0
    /*
        vector<Level_leq_2_Tree> Completions() const
        {
            vector<Level_leq_2_Tree> v;
            if (degree == DEGREE::ONE)
            {
                //degree 0, on completion
                return v;
            }
    
            if (degree == DEGREE::ONE)
            {
                // degree 1, unuqei completion
                v.emplace_back( Level_leq_2_Tree(
                                    Level_leq_1_Component().Completion(),
                                    Tree_2()                       ));
                return v;
            }
    
            // now degree 2 or 2left
            auto P = FinalLevelOneTree();
    
            auto new_2(Tree_2());
    
            auto ucf_2 = Tree_2().EntireEntryInDomain(node_minus_2);
    
            new_2.AddChildBelow(ucf_2);
    
            v.emplace_back(Level_leq_2_Tree(
                               Tree_1(),
                               new_2            ));
            // degree 0 extention
    
    
            if (degree == DEGREE::TWO)
            {
    
                for (auto i = P.Root()->FirstChild();
                        i != nullptr;
                        i = P.NextEnumerate(i)
                    )
                {
                    new_2 = Tree_2();
                    auto ucf_1 = P.CreateHangingSequenceFromUCF(i);
                    new_2.AddChildBelow(ucf_2, ucf_1);
                    v.emplace_back(Level_leq_2_Tree(
                                       Tree_1(),
                                       new_2            ));
                }
            }
    
            if (degree == DEGREE::TWOLEFT)
            {
    
                for (auto i = P.Root()->FirstChild();
                        i != nullptr;
                        i = P.NextEnumerate(i)
                    )
                {
                    new_2 = Tree_2();
                    auto ucf_1 = P.CreateHangingSequenceFromUCF(i);
                    new_2.AddSiblingLeft(ucf_2, ucf_1);
                    v.emplace_back(Level_leq_2_Tree(
                                       Tree_1(),
                                       new_2            ));
                }
            }
    
            return v;
        }*/
    
    // the partial tree si deg 1
    // unuqe ciompletion
    // or degree 2, give the completion of degree 0 at the hanging node
    //
    Level_leq_2_Tree Completion() const
    {
        if (Degree() == DEGREE::ONE)
        {
            auto out_1 = Level_leq_1_Component().Completion();
            auto out_2 = Tree_2();
            return Level_leq_2_Tree (
                       std::move (out_1),
                       std::move (out_2) );
        }
        
        auto out_1 = Tree_1();
        
        auto out_2 (Tree_2() );
        auto && ucf_2 = Tree_2().EntireEntryInDomain (std::get<2> (node_minus) );
        out_2.Add (ucf_2, direction);
        
        return Level_leq_2_Tree (
                   std::move (out_1),
                   std::move (out_2) );
    }
    
    tuple<Level_leq_2_Tree, Level_leq_2_TreeNode, DIRECTION> CompletionWithNode() const
    {
        if (Degree() == DEGREE::ONE)
        {
        
        
            tuple<Level_leq_2_Tree, Level_leq_2_TreeNode, DIRECTION>  output
            {
                Tree(),
                Level_leq_2_TreeNode(),
                DIRECTION::DOWN
            };
            
            auto node = std::get<0> (output).tree_1.AddChildBelow (std::get<1> (NodeMinusSequence() ) );
            
            std::get<1> (output) = Level_leq_2_TreeNode
            {
                DEGREE::ONE,
                node,
                nullptr
            };
            return output;
        }
        
        
        
        tuple<Level_leq_2_Tree, Level_leq_2_TreeNode, DIRECTION>  output
        {
            Tree(),
            Level_leq_2_TreeNode(),
            direction
        };
        
        auto node = std::get<0> (output).tree_2.Add (std::get<2> (NodeMinusSequence() ), direction);
        
        std::get<1> (output) = Level_leq_2_TreeNode
        {
            DEGREE::TWO,
            nullptr,
            node
        };
        
        return output;
        
    }
    
    
    
    tuple<Level_leq_2_Tree, Level_leq_2_TreeNode, DIRECTION> CompletionWithNode (const SingleSequence & ucf_1) const
    {
    
        tuple<Level_leq_2_Tree, Level_leq_2_TreeNode, DIRECTION>  output
        {
            Tree(),
            Level_leq_2_TreeNode(),
            direction
        };
        
//
//        auto out_1 = Tree_1();
//
//        auto out_2 (Tree_2() );

        auto && ucf_2 = Tree_2().EntireEntryInDomain (std::get<2> (node_minus) );
        auto node = std::get<0> (output).tree_2.Add (ucf_2, direction, ucf_1);
        
        std::get<1> (output) = Level_leq_2_TreeNode
        {
            DEGREE::TWO,
            nullptr,
            node
        };
        
        return output;
    }
    
    
    // the partial tree has deg 2
    // completion depends on the new ucf on level-2 tree
    Level_leq_2_Tree Completion (const SingleSequence & ucf_1) const
    {
        auto out_1 = Tree_1();
        
        auto out_2 (Tree_2() );
        auto && ucf_2 = Tree_2().EntireEntryInDomain (std::get<2> (node_minus) );
        out_2.Add (ucf_2, direction, ucf_1);
        
        return Level_leq_2_Tree (
                   std::move (out_1),
                   std::move (out_2) );
    }
    
    leq_2_Sequence CreateHangingSequence() const
    {
        return tree.CreateHangingSequenceFromUCF (node_minus, direction);
    }
};


class LevelThreeTree: public FuncTree < SingleSequence, PartialLevel_leq_2_Tree>
{

private:

    //s is a node in the tree
    // add nodes below s whose domain forms a level-1 tree K
    void AddNodesBelowFromInput (const string & name,
                                 LevelThreeTreeNode * const s,
                                 const LevelOneTree & K,
                                 const int & d)
    {
        if (s->IsEmpty() )
        {
            // if the node is empty,
            // only need to choose the degree
            for (auto e = K.SmallestNode(); e != K.Root(); e = e->BKRight() )
            {
                cout << endl << EmptyString (d) << "What is the degree of "
                     << name
                     << "("
                     << ::to_string (K.EntireEntry (e) )
                     << ")"
                     << " ? ";
                     
                int k;
                cin >> k;
                while (k < 0 || k > 2)
                {
                    cout << EmptyString (d) << "Error: Out of range! ";
                    cin >> k;
                }
                if (k == 0)
                {
                    Add_0();
                }
                else if (k == 1)
                {
                    Add_1();
                }
                else
                {
                    Add_2();
                }
            }
            return;
        }
        
        // now the node is nonempty
        
        
        Level_leq_2_Tree Q;
        
        SingleSequence ucf_21;
        DEGREE degree_of_completion;
        
        for (auto e = K.SmallestNode(); e != K.Root(); e = e->BKRight() )
        {
            // first, need to choose the completion
            
            if (Degree (s) == DEGREE::ONE)
            {
                auto temp = EntireEntryInDomain (s);
                temp.emplace_back (K.EntireEntry (e) );
                
                // if degree one,
                // unique completion
                cout << EmptyString (d + indent)
                     << name
                     << "("
                     <<::to_string (temp)
                     << ")"
                     << " has a unique completion." << endl;
                Q = Value (s).Completion();
            }
            else
            {
                auto temp = EntireEntryInDomain (s);
                temp.emplace_back (K.EntireEntry (e) );
                
                // if degree two , need to choose comletion
                cout << EmptyString (d)
                     << "choose the completion of "
                     << name
                     << "("
                     << ::to_string (temp)
                     << ")"
                     << ":" << endl;
                auto P = Value (s).final_tree_with_node.first;
                // that is , choose the hanging node of the
                //  partial level-1 tree (P, *)
                vector<SingleSequence> pp;
                
                for (auto p = P.Root()->first_child; p != nullptr; p = P.NextEnumerate (p) )
                {
                    pp.emplace_back (P.EntireEntry (p) );
                }
                
                cout << EmptyString (d)
                     << "Possible values of hanging node from the final level-1 tree: "
                     << endl;
                     
                for (unsigned long i = pp.size(); i != 0; --i)
                {
                
                    auto newnode = P.CreateHangingSequenceFromUCF (pp [i - 1]);
                    
                    cout << EmptyString (d + indent) << pp.size() - i + 1 << ". "
                         << ::to_string (newnode);
                }
                cout << EmptyString (d + indent) << pp.size() + 1 << ". "
                     << "-1";
                     
                cout << endl << EmptyString (d) << "Which one? ";
                unsigned k;
                cin >> k;
                
                while (k <= 0 || k > pp.size() + 1)
                {
                    cout << EmptyString (d) << "Error: Out of range! ";
                    cin >> k;
                }
                
                if (k < pp.size() + 1)
                {
                    // if choose degree 1, record it down for later use
                    // and record the ucf_21
                    // otherwise, the degree is 0 by default
                    degree_of_completion = DEGREE::ONE;
                    ucf_21 =  pp[pp.size() - k];
                    Q = Value (s).Completion (ucf_21);
                }
                else
                {
                    // if choose degre 0, Q is the deg-0 completion
                    degree_of_completion = DEGREE::ZERO;
                    Q = Value (s).Completion();
                }
                
            }
            
            // finished cvhoosing completion
            
            // choose hanging node
            auto temp = EntireEntryInDomain (s);
            temp.emplace_back (K.EntireEntry (e) );
            cout << EmptyString (d)
                 << "creating a hanging node for " << name
                 << "("
                 <<::to_string (temp)
                 << ")"
                 << endl;
                 
            cout << endl << EmptyString (d + indent)
                 << "What is the degree of the hanging node ? ";
                 
            int k;
            cin >> k;
            while (k < 0 || k > 2)
            {
                cout << EmptyString (d) << "Error: Out of range! ";
                cin >> k;
            }
            if (k == 0)
            {
                // chosen degree 0
                if (Degree (s) == DEGREE::ONE)
                    // degree of s is 1
                    Add_10 ( s, DIRECTION::DOWN);
                else
                    // degree of s is 2
                    if (degree_of_completion == DEGREE::ZERO)
                        // completion has degree 0
                        Add_200 (s, DIRECTION::DOWN);
                    else
                        // completion has degree 1
                        Add_210 ( s, DIRECTION::DOWN, ucf_21);
            }
            else if (k == 1)
            {
                // chosen degree 1
                // need to specify the hangin node in the level-1 tree part
                
                vector<SingleSequence> qq;
                
                for (auto p = Q.tree_1.Root(); p != nullptr; p = Q.tree_1.NextEnumerate (p) )
                {
                    qq.emplace_back (Q.tree_1.EntireEntry (p) );
                }
                // root can be the ucf of hanging node
                //      for conneveinece
                
                cout << EmptyString (d + indent)
                     << "Possible values of the hanging node: "
                     << endl;
                     
                for (unsigned long i = qq.size(); i != 0; --i)
                {
                
                    auto newnode = Q.CreateHangingSequenceFromUCF_1 (qq [i - 1]);
                    
                    cout << EmptyString (d + indent) << qq.size() - i + 1 << ". "
                         << ::to_string (newnode);
                }
                
                cout << endl << EmptyString (d) << "Which one? ";
                unsigned k;
                cin >> k;
                
                while (k <= 0 || k > qq.size() )
                {
                    cout << EmptyString (d) << "Error: Out of range! ";
                    cin >> k;
                }
                
                //  record it down
                // otherwise, the degree is 0 by default
                auto ucf_31 =  qq[qq.size() - k];
                
                if (Degree (s) == DEGREE::ONE)
                    Add_11 (s, DIRECTION::DOWN, ucf_31);
                    
                else if (degree_of_completion == DEGREE::ZERO)
                    Add_201 (s, DIRECTION::DOWN, ucf_31);
                    
                else
                    Add_211 (s, DIRECTION::DOWN, ucf_21,  ucf_31);
            }
            else
            {
                // chosen degree 2
                // need to specify the hangin node in the level-2 tree part
                // and direction
                vector<DoubleSequence> qq_down, qq_left;
                
                for (auto p = Q.tree_2.Root(); p != nullptr; p = Q.tree_2.NextEnumerate (p) )
                {
                    if (Q.tree_2.Degree (p) == DEGREE::ONE)
                    {
                        qq_down.emplace_back (Q.tree_2.EntireEntryInDomain (p) );
                    }
                }
                for (auto p = Q.tree_2.Root()->FirstChild(); p != nullptr; p = Q.tree_2.NextEnumerate (p) )
                {
                    qq_left.emplace_back (Q.tree_2.EntireEntryInDomain (p) );
                }
                
                cout << EmptyString (d + indent)
                     << "Possible values of the hanging node: "
                     << endl;
                     
                for (unsigned long i = qq_down.size(); i != 0; --i)
                {
                
                    auto newnode = Q.CreateHangingSequenceFromUCF_2 (
                                       qq_down [i - 1], DIRECTION::DOWN);
                                       
                    cout << EmptyString (d + indent) << qq_down.size() - i + 1 << ". "
                         << ::to_string (newnode);
                }
                
                for (unsigned long i = qq_left.size(); i != 0; --i)
                {
                
                    auto newnode = Q.CreateHangingSequenceFromUCF_2 (
                                       qq_left [i - 1], DIRECTION::LEFT);
                                       
                    cout << EmptyString (d + indent) << qq_left.size() - i + 1 + qq_down.size()
                         << ". "
                         << ::to_string (newnode);
                }
                
                cout << endl << EmptyString (d) << "Which one? ";
                unsigned k;
                cin >> k;
                
                while (k <= 0 || k > qq_down.size() + qq_left.size() )
                {
                    cout << EmptyString (d) << "Error: Out of range! ";
                    cin >> k;
                }
                
                //  record it down
                // otherwise, the degree is 0 by default
                
                DIRECTION i2;
                DoubleSequence ucf_32;
                
                if (k <= qq_down.size() )
                {
                    i2 = DIRECTION::DOWN;
                    ucf_32 = qq_down[qq_down.size() - k];
                }
                else
                {
                    i2 = DIRECTION::LEFT;
                    ucf_32 = qq_left[qq_down.size() + qq_left.size() - k];
                }
                
                if (Degree (s) == DEGREE::ONE)
                    Add_12 (s, DIRECTION::DOWN, ucf_32, i2);
                    
                else if (degree_of_completion == DEGREE::ZERO)
                    Add_202 ( s, DIRECTION::DOWN, ucf_32, i2);
                    
                else
                    Add_212 (s, DIRECTION::DOWN, ucf_21, ucf_32, i2);
            }
        }
    }
    
    
public:

    string ShortString (const LevelThreeTreeNode * const s) const
    {
        if (s->IsEmpty() )
        {
            return "";
        }
        string output;
        if (s->Parent()->IsNonEmpty() )
        {
            if (Degree (s->Parent() ) == DEGREE::TWO)
            {
                auto && partial = Partial (s);
                if (partial.Degree() == DEGREE::ZERO)
                {
                    output += "(-1)";
                }
                else
                {
                    output += ::to_string (partial.CreateHangingSequence() );
                }
                output += " | ";
            }
        }
        
        output += ::to_string (Value (s).CreateHangingSequence() );
        return output;
    }
    
    string to_string (const unsigned & d = 0) const
    {
    
        auto current_tree = Root();
        auto temp_tree = current_tree;
        int depth = 0;
        string output;
        
        while (true)
        {
            temp_tree = temp_tree->LastChild();
            
            if (temp_tree != nullptr)
            {
                current_tree = temp_tree;
                
                ++ depth;
                
                vector<LevelThreeTreeNode*> history;
                
                auto record = current_tree->Parent();
                for (int a = depth - 1; a > 0; --a)
                {
                    history.emplace_back (record);
                    record = record -> Parent();
                }
                
                output += EmptyString (d);
                if (depth >= 2)
                {
                    for (int a = depth - 2; a >= 0; --a)
                    {
                        if (history[a]->IsLastBitLeftMost() )
                            output += " \t";
                        else
                            output += "|\t";
                    }
                }
                
                output += "+";
                output += string (interval, '-');
                output += ShortString (current_tree);
                output += "\n";
                
                continue;
            }
            
            while (current_tree != nullptr && current_tree->Left() == nullptr)
            {
                current_tree = current_tree->Parent();
                --depth;
            }
            
            if (current_tree == nullptr)
            {
                return output;
            }
            
            temp_tree = current_tree;
            current_tree = current_tree->Left();
            temp_tree = current_tree;
            
            vector<LevelThreeTreeNode*> history = vector<LevelThreeTreeNode*> ();
            auto record = current_tree->Parent();
            for (int a = depth - 1; a > 0; --a)
            {
                history.emplace_back (record);
                record = record -> Parent();
            }
            
            
            output += EmptyString (d);
            if (depth >= 2)
            {
            
                for (int a = depth - 2; a >= 0 ; --a)
                {
                    if (history[a]->IsLastBitLeftMost() )
                        output += " \t";
                    else
                        output += "|\t";
                }
            }
            output += "+";
            output += string (interval, '-');
            output += ShortString (current_tree);
            
            output += "\n";
            
        }
        return output;
        
    }
    
    
    LevelThreeTree () = default;
    
    LevelThreeTree (const LevelThreeTree& Q) = default;
    
    LevelThreeTree (LevelThreeTree && f) :
        FuncTree<SingleSequence, PartialLevel_leq_2_Tree> (std::move (f) ) {}
        
    LevelThreeTree& operator= (LevelThreeTree T)
    {
        swap (*this, T);
        return *this;
    }
    
    ~LevelThreeTree() = default;
    
    //the degree of the partial level <=2 tree Q(s)
    // 0,1,2
    DEGREE Degree (const LevelThreeTreeNode * const s) const
    {
        return Value (s).Degree();
    }
    
    DIRECTION Direction (const LevelThreeTreeNode * const s) const
    {
        return Value (s).Direction();
    }
    DEGREE Degree (const DoubleSequence & s) const
    {
        return Value (MyNodeInDomain (s) ).Degree();
    }
    
    DIRECTION Direction (const DoubleSequence & s) const
    {
        return Value (MyNodeInDomain (s) ).Direction();
    }
    /*
        SingleSequence SequenceMinusValue_1 (const LevelThreeTreeNode * const s) const
        {
            // the degree-1 ucf as a sinle sequence
            // when Y(s) degree 1
            auto && current_partial_tree = s->LastEntry().second;
            return current_partial_tree.NodeMinusSequence_1();
        }
    
        DoubleSequence SequenceMinusValue_2 (const LevelThreeTreeNode * const s) const
        {
            // the degree-2 ucf as a sinle sequence
            // when Y(s) degree 2
            auto && current_partial_tree = s->LastEntry().second;
            return current_partial_tree.NodeMinusSequence_2();
        }*/
    
    leq_2_Sequence SequenceMinusValue (const LevelThreeTreeNode * const s) const
    {
        return s->LastEntry().second.NodeMinusSequence();
    }
    
    const FinalTreeWithNode & Final (const LevelThreeTreeNode * const s) const
    {
        return s->LastEntry().second.final_tree_with_node;
    }
    
    // the partial level-1 tree in the extra node
    //       of the completion of prev partial level<=2 tree
    const PartialLevelOneTree & Partial (const LevelThreeTreeNode * const s) const
    {
        auto && X = TreeValue (s);
        auto && x = Value (s->Parent() ).CreateHangingSequence();
        return X.tree_2.Value (std::get<2> (x) );
    }
    
    //input the tree
    void Input (const string name = "", const unsigned long d = 0)
    {
        LevelThreeTreeNode * current = Root();
        
        while (true)
        {
            string nodename = ::to_string (EntireEntryInDomain (current) );
            
            LevelOneTree  K ;
            
            if (Degree (current) == DEGREE::ZERO && current->IsNonEmpty() )
            {
                cout << EmptyString (d) << nodename << " has degree 0. It must be terminal" << endl;
            }
            else
            {
                string level_1_tree_name = name + "{" + nodename + "}";
                cout << EmptyString (d) << "Immediate successors of " << name << " at "
                     << StringInDomain (current)
                     << " forms a level-1 tree " << level_1_tree_name  << " :" << endl;
                     
                cout << endl;
                K.Input (level_1_tree_name , d + indent);
                cout << endl;
            }
            
            if (K.IsTrivial() )
            {
                if (current->IsEmpty() )
                {
                    cout << EmptyString (d) << "Level-3 tree " << name << " input complete!" << endl;
                    return;
                }
                while (current->IsLastBitRightMost() )
                {
                    current = current->parent;
                    if (current->IsEmpty() )
                    {
                        cout << EmptyString (d) << "Level-3 tree " << name << " input complete!" << endl;
                        return;
                    }
                }
                current = current->right;
            }
            else
            {
                AddNodesBelowFromInput (name, current, K , d + indent);
                current = current->first_child;
            }
        }
    }
    
    //the tree component of Q(s)
    const Level_leq_2_Tree & TreeValue (const DoubleSequence & s) const
    {
        return Value (s).Tree();
    }
    const Level_leq_2_Tree & TreeValue (const LevelThreeTreeNode * const s) const
    {
        return Value (s).Tree();
    }
    
    /*
        //the completion node of Q(s)
        vector<Level_leq_2_Tree> CreateCompletions (const DoubleSequence & s) const
        {
            return Value(s).Completions();
        }
        vector<Level_leq_2_Tree> CreateCompletions (const LevelThreeTreeNode * const s) const
        {
            return Value(s).Completions();
        }*/
    
    
    
    // if i want to add a node below / left of s
    // what is the tree component of the new node?
    // the prede of the new node has degree 1 or 2 but cshoose the deg 0 extension
    Level_leq_2_Tree NewLevel_leq_2_Tree (LevelThreeTreeNode * const s,
                                          const DIRECTION & i)
    {
        if (i == DIRECTION::DOWN)
        {
            if (s->IsNonEmpty() )
                return Value (s).Completion();
            else
                return Level_leq_2_Tree();
        }
        else
        {
            if (s->Parent()->IsNonEmpty() )
                return Value (s->Parent() ).Completion();
            else
                return Level_leq_2_Tree();
        }
    }
    
    // if i want to add a node below / left of s
    // what is the tree component of the new node?
    // the prede of the new node has degree 2 and
    //      choose the completion of degree 1, ucf u
    Level_leq_2_Tree NewLevel_leq_2_Tree (LevelThreeTreeNode * const s,
                                          const DIRECTION & i,
                                          const SingleSequence & u)
    {
        if (i == DIRECTION::DOWN)
        {
            if (s->IsNonEmpty() )
                return Value (s).Completion (u);
            else
                return Level_leq_2_Tree();
        }
        else
        {
            if (s->Parent()->IsNonEmpty() )
                return Value (s->Parent() ).Completion (u);
            else
                return Level_leq_2_Tree();
        }
    }
    
    
    // add a new node of degree 0 below root, or left of s
    LevelThreeTreeNode *  Add_0 (LevelThreeTreeNode * const s)
    {
        DIRECTION i = (s == Root() ? DIRECTION::DOWN : DIRECTION::LEFT);
        return ::Add (*this,
                      s,
                      i,
                      PartialLevel_leq_2_Tree (DEGREE::ZERO) );
    }
    
    LevelThreeTreeNode * Add_0 ()
    {
        return ::Add ( *this,
                       Root(),
                       DIRECTION::DOWN,
                       PartialLevel_leq_2_Tree (DEGREE::ZERO) );
    }
    
    
    // add a  new node of degree 1 below root, or left of s
    LevelThreeTreeNode *  Add_1 (LevelThreeTreeNode * const s)
    {
        DIRECTION i = (s == Root() ? DIRECTION::DOWN : DIRECTION::LEFT);
        return ::Add (*this,
                      s,
                      i,
                      PartialLevel_leq_2_Tree (DEGREE::ONE) );
    }
    
    LevelThreeTreeNode * Add_1 ()
    {
        return ::Add ( *this,
                       Root(),
                       DIRECTION::DOWN,
                       PartialLevel_leq_2_Tree (DEGREE::ONE) );
    }
    
    
    // add a  new node of degree 2 below root
    LevelThreeTreeNode *  Add_2 (LevelThreeTreeNode * const s)
    {
        DIRECTION i = (s == Root() ? DIRECTION::DOWN : DIRECTION::LEFT);
        return ::Add (*this,
                      s,
                      i,
                      PartialLevel_leq_2_Tree (DEGREE::TWO) );
    }
    LevelThreeTreeNode * Add_2 ()
    {
        return ::Add ( *this,
                       Root(),
                       DIRECTION::DOWN,
                       PartialLevel_leq_2_Tree (DEGREE::TWO) );
    }
    
    
    
    // s has degree 1, so the value has a unique completion
    // the new node has degree 0
    // add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_10 (LevelThreeTreeNode * const s,
                                  const DIRECTION & i3)
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree) );
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_10 (const DoubleSequence & s,
                                  const DIRECTION & i3)
    {
        return Add_10 (this->MyNodeInDomain (s), i3);
    }
    
    
    // s has degree 1, so the value has a unique completion
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_11 (LevelThreeTreeNode * const s,
                                  const DIRECTION & i3,
                                  const SingleSequence & ucf_31)
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_31);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_11 (const DoubleSequence & s,
                                  const DIRECTION & i3,
                                  const SingleSequence & ucf_31)
    {
        return Add_11 (this->MyNodeInDomain (s), i3, ucf_31);
    }
    
    
    // s has degree 1, so the value has a unique completion
    // add a new node in dhe diriciton i3
    // the hanging node  of the new partial level <=2 treegoes in the direction i2, with ucf ucf_32
    LevelThreeTreeNode *  Add_12 (LevelThreeTreeNode * const s,
                                  const DIRECTION & i3,
                                  const DoubleSequence & ucf_32,
                                  const DIRECTION & i2)
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_32, i2);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    LevelThreeTreeNode *  Add_12 (const DoubleSequence & s,
                                  const DIRECTION & i3,
                                  const DoubleSequence & ucf_32,
                                  const DIRECTION & i2
                                 )
    {
        return Add_12 (this->MyNodeInDomain (s), i3, ucf_32, i2);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 0
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_200 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3
                                  )
                                  
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree) );
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_200 (const DoubleSequence & s,
                                   const DIRECTION & i3
                                  )
    {
        return Add_200 (this->MyNodeInDomain (s) , i3);
    }
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_201 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_31)
                                   
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_31);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_201 (const DoubleSequence & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_31)
    {
        return Add_201 (this->MyNodeInDomain (s), i3, ucf_31);
    }
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 2, with ucf ucf_32
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_202 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2
                                  )
                                  
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_32, i2);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_202 (const DoubleSequence & s,
                                   const DIRECTION & i3,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2
                                  )
    {
        return Add_202 (this->MyNodeInDomain (s), i3, ucf_32, i2);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 1 in the hanging node
    //      in the level-2 part, with ucf ucf_21
    // the new node has degree 0
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_210 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21)
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3, ucf_21);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree) );
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_210 (const DoubleSequence & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21)
    {
        return Add_210 (this->MyNodeInDomain (s), i3, ucf_21);
    }
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_211 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const  SingleSequence & ucf_31)
                                   
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3, ucf_21);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_31);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_211 (const DoubleSequence & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const SingleSequence & ucf_31)
    {
        return Add_211 (this->MyNodeInDomain (s), i3, ucf_21, ucf_31);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 1 in the hanging node
    //      in the level-2 part, with ucf ucf_21
    // the new node has degree 2, with direction i2 and ucf ucf_32
    //add a node , eithe child of s or an elder sister of s
    LevelThreeTreeNode *  Add_212 (LevelThreeTreeNode * const s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2
                                  )
    {
        auto && new_tree = NewLevel_leq_2_Tree (s, i3, ucf_21);
        auto && new_partial_tree = PartialLevel_leq_2_Tree (std::move (new_tree), ucf_32, i2);
        
        return ::Add (*this, s, i3, std::move (new_partial_tree) );
    }
    
    LevelThreeTreeNode *  Add_212 (const DoubleSequence & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2
                                  )
    {
        return Add_212 (this->MyNodeInDomain (s), i3, ucf_21, ucf_32, i2);
    }
    
};



DEGREE Degree (const Level_222_FactorNode & s)
{
    return std::get<0> (s);
}

LevelOneTreeNode* NodeInTree_1 (const Level_222_FactorNode & s)
{
    return std::get<1> (s);
}

Level_121_FactorNode* NodeInFactor_1 (const Level_222_FactorNode & s)
{
    return std::get<2> (s);
}

LevelTwoTreeNode* NodeInTree_2 (const Level_222_FactorNode & s)
{
    return std::get<3> (s);
}

FuncTreeNode<SingleSequence, Level_221_Desc> * NodeInFactor_2 (const Level_222_FactorNode & s)
{
    return std::get<4> (s);
}

Level_leq_2_TreeNode NodeInTree (const Level_222_FactorNode & s)
{
    if (Degree (s) == DEGREE::ZERO)
    {
        return Level_leq_2_TreeNode (DEGREE::ZERO,
                                     nullptr,
                                     nullptr);
    }
    if (Degree (s) == DEGREE::ONE)
    {
        return Level_leq_2_TreeNode (DEGREE::ONE,
                                     NodeInTree_1 (s),
                                     nullptr);
    }
    return Level_leq_2_TreeNode (DEGREE::TWO,
                                 nullptr,
                                 NodeInTree_2 (s) );
}



// remove a node in the level-222-factor
//      returns the node to the right (if degree 2 and right exists)
//              or the parent node (otherwise)
Level_222_FactorNode Level_222_Factor::Remove
(const Level_222_FactorNode & s)
{

    if (Degree (s) == DEGREE::ONE)
    {
        auto && p_tree = domain.tree_1.Remove (NodeInTree_1 (s) );
        auto && p_factor = factor_1.Remove (NodeInFactor_1 (s) );
        return Level_222_FactorNode (DEGREE::ONE,
                                     p_tree,
                                     p_factor,
                                     nullptr,
                                     nullptr);
    }
    else
    {
        auto && p_tree = domain.tree_2.Remove (NodeInTree_2 (s) );
        auto && p_factor = factor_2.Remove (NodeInFactor_2 (s) );
        return Level_222_FactorNode (DEGREE::TWO,
                                     nullptr,
                                     nullptr,
                                     p_tree,
                                     p_factor);
    }
}


class Level_322_Desc
{

    friend pair<leq_2_Sequence, DIRECTION> BaseUCF (
        const Level_322_Desc &,
        const Level_leq_2_Tree &);
        
        
public:
    STATE                           state;
    // is the desc valid or nod?
    
    DoubleSequence                  sequence;
    // dhe node in the tree
    //
    
    Level_222_Factor                factor;
    // the level_222_factor map ,
    // which includes info about the completion if cont at domain
    
    vector<Level_222_FactorNode>  enumeration;
    // the enumeration o f the nodes in the level-222-factro
    
    DIRECTION                   ucf_direction;
    // the ucf direction of the factro
    // when cont type at domain:
    //          DOWN if deg 1,
    //          LEFT if deg 2
    
    Level_222_FactorNode         ucf_at_domain_node;
    // the ucf node of the factor
    
    FinalTreeWithNode                final_tree_with_node;
    // the finall level 1 tree from the partial <=2 tree and
    // the hanging node of final level-1 tree from preveiouo level
    
public:

    string to_string (const unsigned d = 0) const;
    
    const DoubleSequence & GetSequence() const
    {
        return sequence;
    }
    
    const Level_leq_2_Tree & GetTree() const
    {
        return factor.domain;
    }
    
    const LevelOneTree & GetTree_1() const
    {
        return factor.domain.tree_1;
    }
    
    const LevelTwoTree & GetTree_2() const
    {
        return factor.domain.tree_2;
    }
    
    const Level_121_Factor & GetFactor_1() const
    {
        return factor.factor_1;
    }
    
    const FuncTree<SingleSequence, Level_221_Desc> & GetFactor_2() const
    {
        return factor.factor_2;
    }
    
    const Level_222_Factor & GetFactor() const
    {
        return factor;
    }
    
    Level_leq_2_TreeNode UCFInTree() const
    {
        return Level_leq_2_TreeNode (Degree (ucf_at_domain_node),
                                     NodeInTree_1 (ucf_at_domain_node),
                                     NodeInTree_2 (ucf_at_domain_node) );
    }
    
    LevelOneTreeNode * UCFInTree_1()  const
    {
        return NodeInTree_1 (ucf_at_domain_node);
    }
    Level_121_FactorNode * UCFInFactor_1()  const
    {
        return NodeInFactor_1 (ucf_at_domain_node);
    }
    LevelTwoTreeNode * UCFInTree_2()  const
    {
        return NodeInTree_2 (ucf_at_domain_node);
    }
    FuncTreeNode<SingleSequence, Level_221_Desc> * UCFInFactor_2()  const
    {
        return NodeInFactor_2 (ucf_at_domain_node);
    }
    
    
    leq_2_Sequence UCF_Sequence() const
    {
        return factor.EntireEntryInDomain (ucf_at_domain_node);
    }
    
    SingleSequence UCF_Sequence_1() const
    {
        return GetTree_1().EntireEntry (UCFInTree_1() );
    }
    
    DoubleSequence UCF_Sequence_2() const
    {
        return GetTree_2().EntireEntryInDomain (UCFInTree_2() );
    }
    
    
    
    //applyies to degree 1
    //  the ucf21 value at the ucf_domain
    const Level_21_Desc & UCF_21_Desc () const
    {
        return GetFactor_1().Value (UCFInFactor_1() );
    }
    
    //applies to degree 2
    //  the ucf221 value at the ucf_domain
    const Level_221_Desc & UCF_221_Desc () const
    {
        return GetFactor_2().Value (UCFInFactor_2() );
    }
    
    
    ~Level_322_Desc() = default;
    
    Level_322_Desc (Level_322_Desc&& D)
    {
        swap (*this, D);
    }
    
    friend void swap (Level_322_Desc & C,
                      Level_322_Desc & D)
    {
        std::swap (C.state, D.state);
        std::swap (C.sequence, D.sequence);
        swap (C.factor, D.factor);
        std::swap (C.enumeration, D.enumeration);
        std::swap (C.ucf_at_domain_node, D.ucf_at_domain_node);
        std::swap (C.ucf_direction, D.ucf_direction);
        std::swap (C.final_tree_with_node, D.final_tree_with_node);
    }
    
    Level_322_Desc& operator= (Level_322_Desc D)
    {
        swap (*this, D);
        return *this;
    }
    
    //generate a invalid
    Level_322_Desc (const STATE & s) :
        state (STATE::INVALID)
    {}
    
    // the default desc should be (empty, empty)
    // for convenience , set node empty and direction NA, everything empty
    Level_322_Desc() :
        state (STATE::VALID),
        sequence (DoubleSequence() ),
        factor (Level_222_Factor() ),
        enumeration (vector<Level_222_FactorNode> () ),
        ucf_direction (DIRECTION::NA),
        ucf_at_domain_node (zeroLevel_leq_2_FactorNode),
        final_tree_with_node (LevelOneTree(), nullptr)
    {}
    
    //copy the desc, only when D is walid!!
    Level_322_Desc (const Level_322_Desc & D) :
        state (D.state),
        sequence (D.sequence),
        factor (D.factor),
        ucf_direction (D.ucf_direction)
    {
        if (Degree (D.ucf_at_domain_node) == DEGREE::ZERO)
        {
            ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else if (Degree (D.ucf_at_domain_node) == DEGREE::ONE)
        {
            ucf_at_domain_node = factor.MyNodeInDomain (D.factor.EntireEntryInDomain (D.ucf_at_domain_node) );
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else
        {
            ucf_at_domain_node = factor.MyNodeInDomain (D.factor.EntireEntryInDomain (D.ucf_at_domain_node) );
            MakeCopy (final_tree_with_node, D.final_tree_with_node);
        }
        
        for (auto && i : D.enumeration)
        {
            enumeration.emplace_back (factor.MyNodeInDomain (D.factor.EntireEntryInDomain (i) ) );
        }
    }
    
    
    // create a desc whose node is (s), degree is d
    //      factor map factors (trivial, *,*)
    //                  which is trivial
    Level_322_Desc (const SingleSequence & s,
                    const DEGREE & d)
        :
        state (STATE::VALID),
        sequence (DoubleSequence {s}),
             factor (Level_222_Factor() )
    {
        if (d == DEGREE::ZERO)
        {
            enumeration = vector<Level_222_FactorNode> ();
            ucf_direction = DIRECTION::NA;
            ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else if (d == DEGREE::ONE)
        {
            enumeration = vector<Level_222_FactorNode> {factor.Root_1() };
            ucf_direction = DIRECTION::DOWN;
            ucf_at_domain_node = enumeration.back();
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else
        {
            enumeration = vector<Level_222_FactorNode> {factor.Root_2() };
            ucf_direction = DIRECTION::DOWN;
            ucf_at_domain_node = enumeration.back();
            final_tree_with_node = factor.domain.tree_2.Root()->LastEntry().second.CompletionWithNode();
        }
    }
    
    
    bool IsConstant() const
    // is it constant?
    {
        return sequence.empty();
    }
    
    
    bool IsContinuousTypeAtDomain() const
    // is the node at domain continuous type at domain?
    {
        return (! (IsConstant() ) ) && sequence.size() + 2 == factor.Cardinality() ;
    }
    
    bool IsDiscontinuousTypeAtDomain() const
    // is it discontinuous typE?
    {
        return ! (IsContinuousTypeAtDomain() );
    }
    
    
    bool IsContinuousType_Star (const Level_leq_2_Tree & T,
                                const Level_leq_2_Tree & Q) const
    {
        return factor.IsContinuous (T, Q, ucf_at_domain_node , ucf_direction);
    }
    
    
    bool IsDiscontinuousType_Star (const Level_leq_2_Tree & T,
                                   const Level_leq_2_Tree & Q) const
    {
        if (IsDiscontinuousTypeAtDomain() )
        
        {
            return ! factor.IsContinuous (T, Q, ucf_at_domain_node , ucf_direction);
        }
        
        else
        {
            return ! factor.IsContinuous (T, Q, ucf_at_domain_node, DIRECTION::LEFT);
            
        }
    }
    
    
    
    /*
        bool operator == (const Level_322_Desc & D) const
        {
            if (ucf_direction != D.ucf_direction)
            {
                return false;
            }
            if (sequence != D.sequence)
            {
                return false;
            }
            if (factor != D.factor)
            {
                return false;
            }
            return true;
        }
    
    
        bool operator != (const Level_322_Desc & D) const
        {
            return ! (*this == D);
        }
    */
// don't need them anyway
    bool operator == (const Level_322_Desc & D) const = delete;
    bool operator != (const Level_322_Desc & D) const = delete;
    
    
    void DiscontinuousTrim()
    {
        // if the node in the level-3 tree ends with -1
        //
        // remove the last node of factor and the -1
        
        if (IsContinuousTypeAtDomain() )
        {
            enumeration.pop_back();
            if ( (Degree (ucf_at_domain_node) == DEGREE::ONE)
                    ||
                    (NodeInTree_2 (ucf_at_domain_node)->IsLastBitRightMost() )
               )
            {
                ucf_at_domain_node = factor.Remove (ucf_at_domain_node);
                ucf_direction = DIRECTION::DOWN;
            }
            else
            {
                ucf_at_domain_node = factor.Remove (ucf_at_domain_node);
                ucf_direction = DIRECTION::LEFT;
            }
        }
    }
    
    template <typename A>
    void Extend_1 (const LevelThreeTree & Y,
                   const LevelThreeTreeNode * s,
                   A && new_in_image)
    {
    
        if (s == nullptr)
        {
            Extend_1 (std::forward<A> (new_in_image) );
            return;
        }
        
        if (Y.Degree (s) == DEGREE::ZERO)
        {
            Extend_1 (s->LastEntry().first,
                      std::forward<A> (new_in_image) );
            return;
        }
        
        auto && new_ucf = Y.SequenceMinusValue (s);
        auto && new_direction = Y.Direction (s);
        Extend_1 (s->LastEntry().first,
                  std::forward<A> (new_in_image),
                  new_ucf,
                  new_direction);
        return;
    }
    
    template <typename A>
    void Extend_2 (const LevelThreeTree & Y,
                   const LevelThreeTreeNode * s,
                   const PartialLevelOneTree & Ww,
                   A && new_in_image)
    {
        // now s_parent has deg 2
        
        
        auto && W = Ww.Tree();
        auto && w = Ww.NodeMinusInTree();
        
        if (w == nullptr)
        {
            if (s == nullptr)
            {
                Extend_20 (std::forward<A> (new_in_image) );
                return;
            }
            
            if (Y.Degree (s) == DEGREE::ZERO)
            {
                Extend_20 (s->LastEntry().first,
                           std::forward<A> (new_in_image) );
                return;
            }
            
            auto && new_ucf = Y.SequenceMinusValue (s);
            auto && new_direction = Y.Direction (s);
            Extend_20 (s->LastEntry().first,
                       std::forward<A> (new_in_image),
                       new_ucf,
                       new_direction);
            return;
        }
        
        // now s_parent has deg 2 and s chooses the deg 1 complesion,
        // or s = -1 and the desc choose the deg 1 completion
        
        auto && ucf_21 = W.EntireEntry (w);
        
        if (s == nullptr)
        {
            Extend_21 (ucf_21,
                       std::forward<A> (new_in_image) );
            return;
        }
        
        if (Y.Degree (s) == DEGREE::ZERO)
        {
            Extend_21 (s->LastEntry().first,
                       ucf_21,
                       std::forward<A> (new_in_image) );
            return;
        }
        
        auto && new_ucf = Y.SequenceMinusValue (s);
        auto && new_direction = Y.Direction (s);
        Extend_21 (s->LastEntry().first,
                   ucf_21,
                   std::forward<A> (new_in_image),
                   new_ucf,
                   new_direction);
        return;
    }
    
    
    //   *************
    //   add a new node on the leevl_1 component of the factor
    //   (ucf_at_domain is level-1)
    //
    //   the new value is a 21-desc
    //  *****************
    
    template <typename A>
    void Extend_1 (const SingleSequence & extend_node,
                   A && new_in_image,
                   const leq_2_Sequence & new_ucf,
                   const DIRECTION & new_direction)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is not (0,-1)
        //
        
        Extend_1 (extend_node, std::forward<A> (new_in_image) );
        
        ucf_at_domain_node = factor.MyNodeInDomain (new_ucf);
        ucf_direction = new_direction;
        
        if (std::get<0> (new_ucf) == DEGREE::TWO)
        {
            final_tree_with_node = factor.domain.tree_2.CreateFinalTreeWithNodeFromUCF ( NodeInTree_2 (ucf_at_domain_node), new_direction);
        }
    }
    
    
    
    template <typename A>
    void Extend_1 (const SingleSequence & extend_node,
                   A && new_in_image)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        // resulting in a new discontinuous desc, whose ucf is (0,-1)
        //
        
        sequence.emplace_back (extend_node);
        
        auto && new_in_domain = factor.Add (
                                    ucf_at_domain_node,
                                    std::forward<A> (new_in_image) );
                                    
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
        ucf_direction = DIRECTION::NA;
        // direction is NA because deg 0
        
        // final tree was empty to start with, and will remain empty
    }
    
    template <typename A>
    void Extend_1 (A && new_in_image)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        // resulting in a new continuous desc
        //
        
        auto && new_in_domain = factor.Add
                                (ucf_at_domain_node,
                                 std::forward<A> (new_in_image) );
                                 
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = new_in_domain;
        ucf_direction = DIRECTION::DOWN;
        // direction is down by definition
        
        // final tree was empty to start with, and will remain empty
    }
    
    
    //   *************
    //   add a new node on the leevl_1 component of the factor
    //   (ucf_at_domain is leveel-2)
    //
    //  the new noe in the level-2 tree is degree 0
    //
    //   the new value is a 221-desc
    //  *****************
    
    template <typename A>
    void Extend_20 (const SingleSequence & extend_node,
                    A && new_in_image,
                    const leq_2_Sequence & new_ucf,
                    const DIRECTION & new_direction)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new discontinuous desc, whose ucf is not -1
        //
        
        Extend_20 (extend_node, std::forward<A> (new_in_image) );
        
        ucf_at_domain_node = factor.MyNodeInDomain (new_ucf);
        ucf_direction = new_direction;
        
        if (std::get<0> (new_ucf) == DEGREE::TWO)
        {
            final_tree_with_node = factor.domain.tree_2.CreateFinalTreeWithNodeFromUCF ( NodeInTree_2 (ucf_at_domain_node), new_direction);
        }
        else
        {
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
    }
    
    
    
    template <typename A>
    void Extend_20 (const SingleSequence & extend_node,
                    A && new_in_image)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new discontinuous desc, whose ucf is (0,-1)
        //
        
        sequence.emplace_back (extend_node);
        
        auto && new_in_domain = factor.Add (ucf_at_domain_node,
                                            ucf_direction,
                                            std::forward<A> (new_in_image) );
                                            
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
        ucf_direction = DIRECTION::NA;
        
        final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
    }
    
    template <typename A>
    void Extend_20 (A && new_in_image)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new continuous desc
        //
        
        auto && new_in_domain = factor.Add
                                (ucf_at_domain_node,
                                 ucf_direction,
                                 std::forward<A> (new_in_image) );
                                 
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = new_in_domain;
        ucf_direction = DIRECTION::LEFT;
        // direction is left by definition
        
        // final tree doesn't change by defintiion
    }
    
    
    
    //   *************
    //   add a new node on the leevl_1 component of the factor
    //   (ucf_at_domain is leveel-2)
    //
    //  the new noe in the level-2 tree is degree 1
    //
    //   the new value is a 221-desc
    //  *****************
    
    template <typename A>
    void Extend_21 (const SingleSequence & extend_node,
                    const SingleSequence & ucf_21,
                    A && new_in_image,
                    const leq_2_Sequence & new_ucf,
                    const DIRECTION & new_direction)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new discontinuous desc, whose ucf is not -1
        //
        
        Extend_21 (extend_node, ucf_21, std::forward<A> (new_in_image) );
        
        ucf_at_domain_node = factor.MyNodeInDomain (new_ucf);
        ucf_direction = new_direction;
        
        if (std::get<0> (new_ucf) == DEGREE::TWO)
        {
            final_tree_with_node = factor.domain.tree_2.CreateFinalTreeWithNodeFromUCF ( NodeInTree_2 (ucf_at_domain_node), new_direction);
        }
        else
        {
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
    }
    
    
    
    template <typename A>
    void Extend_21 (const SingleSequence & extend_node,
                    const SingleSequence & ucf_21,
                    A && new_in_image)
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new discontinuous desc, whose ucf is (0,-1)
        //
        
        sequence.emplace_back (extend_node);
        
        auto && new_in_domain = factor.Add (ucf_at_domain_node,
                                            ucf_direction,
                                            ucf_21,
                                            std::forward<A> (new_in_image) );
                                            
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
        ucf_direction = DIRECTION::NA;
        // direction is NA becuase deg 0
        
        final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        
    }
    
    template <typename A>
    void Extend_21 (const SingleSequence & ucf_21,
                    A && new_in_image )
    {
        // extend the current  desc by one
        //
        // must be discontinuous to start with
        //
        // the new node in the level-2 tree has deg 0
        //
        // resulting in a new continuous desc
        //
        
        auto && new_in_domain = factor.Add
                                (ucf_at_domain_node,
                                 ucf_direction,
                                 ucf_21,
                                 std::forward<A> (new_in_image) );
                                 
        enumeration.emplace_back (new_in_domain);
        
        ucf_at_domain_node = new_in_domain;
        ucf_direction = DIRECTION::LEFT;
        //direction is left by defintion
        
        // final tree doesn't change by defintion
    }
    
    void MoveLastEntryInNode (const LevelThreeTree & Y,
                              const LevelThreeTreeNode * const s)
    {
    
        if (s == nullptr)
        {
            MoveLastEntryInNode ();
            return;
        }
        
        auto && last_entry_in_node = s->LastEntry().first;
        
        if (Y.Degree (s) == DEGREE::ZERO)
        {
            MoveLastEntryInNode (last_entry_in_node);
            return;
        }
        
        auto && new_ucf = Y.Value (s).NodeMinusSequence();
        auto && new_direction = Y.Direction (s);
        
        MoveLastEntryInNode (last_entry_in_node,
                             new_ucf,
                             new_direction);
        return;
    }
    
    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node,
                              const leq_2_Sequence & new_ucf,
                              const DIRECTION & new_direction)
    {
    
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is not (0,-1)
        
        if (sequence.size() > 1)
        {
        
            sequence.back() = last_entry_in_node;
            
            ucf_at_domain_node = factor.MyNodeInDomain (new_ucf);
            ucf_direction = new_direction;
            
            if (std::get<0> (new_ucf) == DEGREE::TWO)
            {
                final_tree_with_node = factor.domain.tree_2.CreateFinalTreeWithNodeFromUCF ( NodeInTree_2 (ucf_at_domain_node), new_direction);
            }
            else
            {
                final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
            }
        }
        else
        {
            *this = Level_322_Desc (last_entry_in_node, std::get<0> (new_ucf) );
        }
    }
    
    void MoveLastEntryInNode (const SingleSequence & last_entry_in_node)
    {
        // current is disc type
        // move the last entry to "last_entry_in_node", which is not -1, and ucf is (0,-1)
        
        if (sequence.size() > 1)
        {
            sequence.back() = last_entry_in_node;
            ucf_at_domain_node = zeroLevel_leq_2_FactorNode;
            ucf_direction = DIRECTION::NA;
            // direction is NA because deg 0
            
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else
        {
            *this = Level_322_Desc (last_entry_in_node,
                                    DEGREE::ZERO);
        }
    }
    
    void MoveLastEntryInNode ()
    {
        //current is disc type
        // move the last entry to -1.
        
        if (sequence.size() == 1)
        {
            state = STATE::INVALID;
            return;
            // no node (-1) can show up iin 332 desc
        }
        
        sequence.pop_back();
        
        ucf_at_domain_node = LastNodeInDomain();
        if (Degree (ucf_at_domain_node) == DEGREE::ONE)
        {
            ucf_direction = DIRECTION::DOWN; //by def
        }
        else
        {
            ucf_direction = DIRECTION::LEFT; // by def
        }
        
        // nneeet do reset the final tree, as the penultimate
        if (Degree (ucf_at_domain_node) == DEGREE::ONE)
        {
            final_tree_with_node = FinalTreeWithNode (LevelOneTree(), nullptr);
        }
        else
        {
        
            auto && X2 = factor.domain.tree_2;
            auto && x = NodeInTree_2 (ucf_at_domain_node);
            
            final_tree_with_node = X2.PresentFinalTreeWithNode (x);
            // x is never root here!!
            // i.e. a nonconstant desc must have a nonempty effective node!!
        }
    }
    
    const Level_222_FactorNode & LastNodeInDomain () const
    {
        return enumeration.back();
    }
};




pair<leq_2_Sequence, DIRECTION> UCF_Star (const Level_21_Desc & D,
        const LevelOneTree & W)
{

    if (D.Degree() == DEGREE::ONE)
        return pair<leq_2_Sequence, DIRECTION> (
                   leq_2_Sequence (DEGREE::ONE,
                                   D.sequence_1,
                                   DoubleSequence() ),
                   DIRECTION::DOWN);
//   if (D.IsContinuousTypeAtDomain())
//
// doesn't matter if D is cont at domain  with  this form
//
    if (D.IsContinuousType_Star (W) )
    {
        if (D.sequence_2.empty() )
        {
            return pair<leq_2_Sequence, DIRECTION> (
                       leq_2_Sequence (DEGREE::ONE,
                                       SingleSequence(),
                                       DoubleSequence() ),
                       DIRECTION::DOWN);
        }
        else
        {
            return pair<leq_2_Sequence, DIRECTION> (
                       leq_2_Sequence (DEGREE::TWO,
                                       SingleSequence(),
                                       D.sequence_2),
                       DIRECTION::LEFT);
        }
    }
    
    else
        return pair<leq_2_Sequence, DIRECTION> (
                   leq_2_Sequence (DEGREE::TWO,
                                   SingleSequence(),
                                   D.sequence_2),
                   DIRECTION::DOWN);
//    else if (D.IsContinuousType_Star (W))
//        return pair<leq_2_Sequence, DIRECTION> (
//                   leq_2_Sequence (DEGREE::TWO,
//                                   SingleSequence(),
//                                   D.sequence_2),
//                   DIRECTION::LEFT);
//    else
//        return pair<leq_2_Sequence, DIRECTION> (
//                   leq_2_Sequence (DEGREE::TWO,
//                                   SingleSequence(),
//                                   D.sequence_2),
//                   DIRECTION::DOWN);
}

pair<leq_2_Sequence, DIRECTION> UCF (const Level_221_Desc & C,
                                     const LevelOneTree & W)
{

    if (C.Degree() == DEGREE::ONE)
        return pair<leq_2_Sequence, DIRECTION> (
                   zero_leq_2_Sequence,
                   DIRECTION::NA);
    if (C.UCFAtDomain() == nullptr)
        return pair<leq_2_Sequence, DIRECTION> (
                   zero_leq_2_Sequence,
                   DIRECTION::NA);
    auto && critical_desc = C.UCF_As21Desc();
    return UCF_Star (critical_desc, W);
    // coulb de leftwards or downlwards
}

//pair<leq_2_Sequence, DIRECTION> UCF_plus (const Level_221_Desc & C,
//        const LevelOneTree & W_plus)
//{
//    auto && critical_desc = C.UCF_As21Desc();
//    return UCF_Star (critical_desc, W_plus);
//    // always downwards
//}

// B is a (*,*,Q)-desc
// get the node and direction as ucf
//      such that C is a (*,*,(W,*))-desc
//
pair<leq_2_Sequence, DIRECTION> BaseUCF (
    const Level_322_Desc & B,
    const Level_leq_2_Tree & Q)
{
    if (Degree (B.ucf_at_domain_node) == DEGREE::ZERO)
    {
        // degree 0
        return pair<leq_2_Sequence, DIRECTION>
               (                   zero_leq_2_Sequence,
                                   DIRECTION::NA) ;
    }
    
    if (Degree (B.ucf_at_domain_node) == DEGREE::ONE)
    {
        //degree 1
        
        auto && critical_desc = B.UCF_21_Desc();
        // the critical desc to examine
        // it is a (T,Q1)-desc
        
        if (critical_desc.Degree() == DEGREE::ONE
                ||
                critical_desc.ucf_at_domain == nullptr)
        {
            return pair<leq_2_Sequence, DIRECTION>
                   (zero_leq_2_Sequence, DIRECTION::NA);
        }
        
        
        auto && ucf_at_Q1 = critical_desc.UCF_As21Desc();
        // the ucf, a single sequence, from a node in Q1
        
        auto && ucf_leq_2_seq = leq_2_Sequence (DEGREE::ONE,
                                                ucf_at_Q1,
                                                DoubleSequence() );
                                                
        return pair<leq_2_Sequence, DIRECTION>
               (std::move (ucf_leq_2_seq),
                DIRECTION::DOWN);
    }
    
    //degree 2
    
    auto && critical_desc = B.UCF_221_Desc();
    
    return UCF (critical_desc, B.final_tree_with_node.first);
//
//    auto && critical_level_2_tree = B.factor.domain.tree_2;
//
//    auto && critical_node_in_level_2_tree = NodeInTree_2 (B.ucf_at_domain_node);
//
//    auto && Ww = critical_level_2_tree.Value (critical_node_in_level_2_tree);
//
//    if (B.ucf_direction == DIRECTION::LEFT)
//    {
//        return UCF (critical_desc,  Ww.Tree() );
//        // maybe leftwards or downwards
//    }
//    else
//    {
//        return UCF (critical_desc,  Ww.Completion() );
//        // always downwards
//    }
}


PartialLevel_leq_2_Tree BasePartialTree (
    const Level_322_Desc & B,
    const Level_leq_2_Tree & Q)
{

    auto && b = BaseUCF (B, Q);
    
    if (std::get<0> (b.first) == DEGREE::ZERO)
    {
        return PartialLevel_leq_2_Tree ( Q );
    }
    if (std::get<0> (b.first) == DEGREE::ONE)
    {
        return PartialLevel_leq_2_Tree ( Q, std::get<1> (b.first) );
    }
    return PartialLevel_leq_2_Tree ( Q, std::get<2> (b.first), b.second);
}


/*
// given D, a (Q,empty)-desc of degree 1
//      that can be extended to a (Q',empty)-desc
// given D' , either nullptr (representing to start extending) or a (Q',empty)-desc whose restriction to (Q,empty) is D,
// move D' to the left of D' whose restriction is still D
// Q' is the completion of (Q,q), q is the hanging node
//
// REMARK: q must have degree 1
//
void MoveToLeft (const Level_21_Desc & D,
                 unique_ptr<Level_21_Desc> & D_prime,
                 const Level_leq_2_Tree & Q,
                 const Level_leq_2_Tree & Q_prime,
                 const Level_leq_2_TreeNode & q)
{

    auto && Q1 = Q.tree_1;
    // the level-1 component of Q
    auto && Q_prime_1 = Q_prime.tree_1;
    // the level-1 component. of Q_prime

    auto && q1 = std::get<1> (q);
    // the level-1 tree node in Q1
    auto && q1_sequence = Q1.EntireEntry (q1);

    if (D_prime == nullptr)
    {
        //starting to move
        // must move to q1
        D_prime.reset (new Level_21_Desc (q1_sequence) );
        return;
        // some room for optimization here
        // q1_sequence copied twice
        // probably minor point, as most desc have degree 2
    }
    else
    {
        // move to the left of D

        auto && q1_left = Left (D_prime->GetSequence_1(), Q_prime_1);
        // we shold move here, a node in Q'_1

        auto && q1_left_to_compare = Left (D.GetSequence_1(), Q1);
        // the bound in Q is here, a node in Q_1

        if (q1_left == nullptr)
        {
            //squeezed out
            // no more
            D_prime.reset (nullptr);
            return;
        }
        if (q1_left_to_compare == nullptr)
        {
            // exists
            D_prime.reset (new Level_21_Desc (Q_prime_1.EntireEntry (q1_left) ) );
            return;
        }

        // both left exists, cnompare them
        if (Q_prime_1.EntireEntry (q1_left) == Q1.EntireEntry (q1_left_to_compare) )
        {
            //squeezed out
            D_prime.reset (nullptr);
            return;
        }
        else
        {
            // still exists
            D_prime.reset (new Level_21_Desc (Q_prime_1.EntireEntry (q1_left) ) );
            return;
        }
    }
}
*/


// given D, a (Q,W)-desc of degree 2, *-W-ucf w or w-   ???
//      that can be extended to a (Q',W)-desc by
//              either moving last entry to q2 , if i=LEFT
//              or attaching (*, q2_last) , if i = DOWN
//
//        ******* or q of deg 1, w is -1, moving to q ******
//
// given D' , either invalid (representing to start extending) or a (Q',W)-desc whose restriction to (Q,W) is D,
// move D' to the left of D' whose restriction is still D
// Q' is a completion of (Q,q), q is the hanging node, goind in the direciton i
//
//
void MoveToLeft (const Level_21_Desc & D,
                 Level_21_Desc & D_prime,
                 const Level_leq_2_Tree & Q_prime,
                 const Level_leq_2_TreeNode & q,
                 const DIRECTION & i,
                 const LevelOneTree & W)
{
    if (D_prime.state == STATE::INVALID)
    {
        // start the computation
        
        if (std::get<0> (q) == DEGREE::ONE)
        {
            // degree one, just set q1
            D_prime = Level_21_Desc (Q_prime.tree_1.EntireEntry (std::get<1> (q) ) );
            return;
        }
        
        // now deg 2
        
        if (i == DIRECTION::LEFT)
        {
        
            // starting to move
            D_prime = D;
            // make a copy of D
            D_prime.DiscontinuousTrim();
            // trim it to disc type at domain
            
            D_prime.MoveLastEntryInNode (Q_prime, q);
            return;
            
        }
        else
        {
            // going down
            
            // starting to add
            D_prime = D;
            // make a copy of D
            
            D_prime.DiscontinuousTrim();
            // trim it to disc type at domain
            
            auto && ucf = D.UCF();
            auto && new_in_image = W.EntireEntry (BKLeft (ucf, W) );
            D_prime.Extend (Q_prime,
                            q,
                            std::move (new_in_image) );
            return;
        }
    }
    
    // now , D' already defined, want to move left
    
    MoveToBKLeft (D_prime, Q_prime, W);
    
    // check if the result extends D_effective_part
    //
    // enough to check node: must be have length >= q2's length
    //                 and if = , last entry must be equal to q2_last
    
    if (std::get<0> (q) == DEGREE::TWO)
    {
    
        auto && q2 = std::get<2> (q);
        auto && length_to_compare = q2->Length();
        auto && length = D_prime.GetSequence_2().size();
        
        if (length > length_to_compare)
        {
            // it works
            return;
        }
        if (length < length_to_compare)
        {
            // it doesn't work
            D_prime.state = STATE::INVALID;
            return;
        }
        // now same length. compare last entry
        if ( q2->LastEntry().first == D_prime.GetSequence_2().back() )
        {
            // it works
            return ;
        }
        else
        {
            // it doesn't work
            D_prime.state = STATE::INVALID;
            return;
        }
    }
    else
    {
        // there is only one desc: use q1
        // so go invalid!!
        D_prime.state = STATE::INVALID;
        return;
    }
}


// given C, a (T,Q,*)-desc
//ucf q-, ucf-dercton  i
// C' , either invalid (standing for starting the computation) or a candidate (T,Q',W)-desc whose restriction to (T,Q) is C,
// produce the left of C' whose restriction to (T,Q) is still C
//          and both the result and C have the common minus-in-base, when i=LEFT
//              C' minus-in-base  = C, when i = DOWN
// Q' is the completion of (Q,q), q is the hanging node whose ucf in Q is goint in the direction i
//
//
void MoveToLeftCandidate (const Level_221_Desc & C,
                          Level_221_Desc & C_prime,
                          const Level_leq_2_Tree & T,
                          const Level_leq_2_Tree & Q_prime,
                          const Level_leq_2_TreeNode & q,
                          const DIRECTION & i,
                          const LevelOneTree & W)
{
    if (C_prime.state == STATE::INVALID)
    {
        // starting to move
        
        C_prime = C;
        C_prime.DiscontinuousTrim();
        // copy C and trim it to disc type
        
        // now we want to extend it by adding the first avaiable 21-desc
        //      and the last node in T2
        
        
        
        auto && critical_21_desc = C.UCF_As21Desc();
        
        Level_21_Desc critical_left (STATE::INVALID);
        
        MoveToLeft (critical_21_desc,
                    critical_left,
                    Q_prime,
                    q,
                    i,
                    W);
                    
        if (critical_left.state == STATE::INVALID)
        {
            C_prime.state = STATE::INVALID;
            //squeezed out
            // no more
            return;
        }
        
        //
        // found the 21-desc to move, and move it
        //
        
        //starting to extend
        
        auto && T2 = T.tree_2;
        auto && node_in_T2 = T2.MyNodeInDomain (C.GetSequence_2() );
        C_prime.Extend (T2,
                        node_in_T2->LastChild(),
                        std::move (critical_left) );
        return;
        
    }
    
    // now C'is not nullptr. it is a valid candidate extension
    
    auto && T2 = T.tree_2;
    auto && node_in_T2 = T2.MyNodeInDomain (C_prime.GetSequence_2() );
    
    auto && effective_length = C_prime.GetSequence_2().size();
    
    // later check if it properly extend the core part of C
    auto && effective_length_to_compare = C.GetSequence_2().size();
    
    if (C_prime.IsDiscontinuousType_Star_As21Desc (Q_prime, W) )
    {
        //C'_effective part can be end extended as (Q',W)-desc
        
        Level_21_Desc critical_21_desc = C_prime.UCF_As21Desc();
        
        if (effective_length > effective_length_to_compare)
        {
            MoveToBKLeft (critical_21_desc, Q_prime, W);
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
            // once transitioning good,
            // automatically good
            //
            auto && bound_in_C =  C.UCF_As21Desc();
            MoveToLeft (bound_in_C,
                        critical_21_desc,
                        Q_prime,
                        q,
                        i,
                        W);
        }
        
        if (critical_21_desc.state == STATE::INVALID)
        {
            //squeezed out
            // no more
            C_prime.state = STATE::INVALID;
            return;
        }
        //found the good transition
        
        
        // now critical_left is the extention of C'_effective part,
        // need to find the node
        
        C_prime.DiscontinuousTrim();
        C_prime.Extend (T2,
                        node_in_T2->LastChild(),
                        std::move (critical_21_desc) );
        return;
    }
    
    else
    {
        //cannot extend C_effective_part
        
        if (effective_length == effective_length_to_compare)
        {
            // C' is C_effective_part exteded by (D,-1), D not extendable
            C_prime.state = STATE::INVALID;
            return;
            // get squeezed out
        }
        
        //otherwise,
        // if node_in_T2 is the root, get sqeezed out
        // if not, move to the left
        
        if (node_in_T2->IsEmpty() )
        {
            // it is (least desc, -1)
            C_prime.state = STATE::INVALID;
            return ;
            // squezed out
        }
        
        //start moving
        
        C_prime.DiscontinuousTrim();
        C_prime.MoveLastEntryInNode (T2,
                                     node_in_T2->Left() );
        return;
    }
}

bool ShowUpInSign (const SingleSequence & s,
                   const Level_21_Desc & D)
{

    if (D.Degree() == DEGREE::ONE)
    {
        return false;
    }
    for (auto && e : D.enumeration)
    {
        if (s == D.factor.Value (e) )
        {
            return true;
        }
    }
    return false;
}


// D is cont at domain to start with
bool ShowUpInSignDiscPart (const SingleSequence & s,
                           const Level_21_Desc & D)
{

    Level_21_Desc E = D;
    E.DiscontinuousTrim();
    
    for (auto && e : E.enumeration)
    {
        if (s == E.factor.Value (e) )
        {
            return true;
        }
    }
    return false;
}

bool ShowUpInBase (const SingleSequence & s,
                   const Level_221_Desc & C)
{

    if (C.Degree() == DEGREE::ONE)
    {
        return false;
    }
    for (auto && e : C.enumeration)
    {
        if (ShowUpInSign (s, C.factor.Value (e) ) )
        {
            return true;
        }
    }
    return false;
}

bool ShowUpInBaseDiscPart (const SingleSequence & s,
                           const Level_221_Desc & C)
{

    Level_221_Desc E = C;
    E.DiscontinuousTrim();
    for (auto && e : E.enumeration)
    {
        if (ShowUpInSign (s, E.factor.Value (e) ) )
        {
            return true;
        }
    }
    return false;
}


//
// w is the last node ow W
// when i3 = DOWN, need to check that w is hit eventually
//
bool Validate (const Level_221_Desc & C,
               Level_221_Desc & C_prime,
               const LevelOneTree & W,
               const LevelOneTreeNode * const w,
               const DIRECTION & i3)
{


    if (i3 == DIRECTION::DOWN)
    
    {
        // neet do theck that w is hit
        if (!ShowUpInBase (W.EntireEntry (w), C_prime) )
        {
            return false;
        }
    }
    
    // need to check it is iindeed a desc!
    
    if (C_prime.IsDiscontinuousTypeAtDomain() )
    {
        return true;
    }
    
    // now C' is cont at domain
    
    if (i3 == DIRECTION::DOWN)
    {
    
        if (ShowUpInBaseDiscPart (W.EntireEntry (w), C_prime) )
        {
            return true;
        }
        auto && last_node_in_C_prime = C_prime.LastNodeInDomain();
        auto && critical_desc = C_prime.GetFactor().Value (last_node_in_C_prime);
        
        if (critical_desc.IsDiscontinuousTypeAtDomain() )
            return true;
            
            
        auto && last_node = critical_desc.LastNodeInDomain();
        auto && last_value = critical_desc.factor.Value (last_node);
        if (last_value != W.EntireEntry (w) )
        {
            return true;
        }
        return false;
    }
    
// now i3 is LEFT
// W was the same from C

    auto && effective_length = C_prime.GetSequence_2().size();
    
    auto && effective_length_to_compare = C.GetSequence_2().size();
    
    if (effective_length > effective_length_to_compare)
    {
        return true;
    }
    
    auto && last_node_in_C_prime = C_prime.LastNodeInDomain();
    auto && critical_desc = C_prime.GetFactor().Value (last_node_in_C_prime);
    auto && critical_factor = critical_desc.GetFactor();
    
    //now C' is C_effe1ctive_part plus (D, -1)
    // we need to make sure of the well-behavior of D
    
    if (critical_desc.IsDiscontinuousTypeAtDomain() )
        return true;
        
        
    auto && last_node = critical_desc.LastNodeInDomain();
    auto && last_value = critical_factor.Value (last_node);
    if (last_value != W.EntireEntry (w) )
    {
        return true;
    }
    
    //otherwise, last value is w
    //then
    return false;
    
}


// when i3 = DOWN, W is the completion of the node in X to bee extended
//
// when i3 = LEFT, W is the tree component of the node in X
//
void MoveToLeft (const Level_221_Desc & C,
                 Level_221_Desc & C_prime,
                 const Level_leq_2_Tree & T,
                 const Level_leq_2_Tree & Q_prime,
                 const Level_leq_2_TreeNode & q,
                 const DIRECTION & i,
                 const LevelOneTree & W,
                 const LevelOneTreeNode * const w,
                 const DIRECTION & i3)
{
    do
    {
        MoveToLeftCandidate (C, C_prime, T, Q_prime, q, i, W);
        
        if (C_prime.state == STATE::INVALID)
        {
            return;
        }
        if (Validate (C, C_prime, W, w, i3) )
        {
            return;
        }
    }
    while (true);
}

// the tree component is already the same to match
bool Match (const PartialLevelOneTree & Ww, const PartialLevelOneTree & Pp)
{
    if (Ww.Degree() != Pp.Degree() )
    {
        return false;
    }
    if (Ww.Degree() == DEGREE::ZERO)
    {
        return true;
    }
    return Ww.SequenceMinus() == Pp.SequenceMinus();
}


// given B, a (Y,T,Q)-desc
// B' , either invalid (standing for starting the computation) or a candidate (B,T,Q')-desc whose restriction to (T,Q) is B,
// produce the left candidate of B' whose restriction to (Y,T,Q) is still B
//
// Q' is the completion of (Q,q), q is the hanging node whose ucf in Q is going in the direction i
//
//
//
//  REMARK: B is a (Y,T, (Q,i,q-)-desc
//
//

void MoveToLeftCandidate (const Level_322_Desc & B,
                          Level_322_Desc & B_prime,
                          const LevelThreeTree & Y,
                          const Level_leq_2_Tree & T,
                          //                     const Level_leq_2_Tree & Q,
                          const Level_leq_2_Tree & Q_prime,
                          const Level_leq_2_TreeNode & q,
                          const DIRECTION & i)
{
    if (B_prime.state == STATE::INVALID)
    {
        // starting
        B_prime = B;
        
        auto && sequence = B.sequence;
        auto && node_in_Y = Y.MyNodeInDomain (sequence);
        
        auto && critical_node = B.ucf_at_domain_node;
        auto && critical_direction = B.ucf_direction;
        auto && factor = B.factor;
        
        if (Degree (critical_node) == DEGREE::ONE)
        {
            // degree is of ucf_at_domoan of B is never 0
            //  as B is a (Y,T, (Q,i,q-))-desc
            
            // first assume degree 1
            // the critical desc is then a (T,Q1)-desc
            
            auto && critical_21_desc = factor.Value_1 (critical_node);
            
            Level_21_Desc critical_left (STATE::INVALID);
            
            MoveToLeft (critical_21_desc,
                        critical_left,
                        T,
                        Q_prime.tree_1,
                        std::get<1> (q) );
            // the next smaller desc
            
            
            if (critical_left.state == STATE::INVALID)
            {
                B_prime.state = STATE::INVALID;
                return;
            }
            
            B_prime.DiscontinuousTrim();
            B_prime.Extend_1 (Y,
                              node_in_Y->LastChild(),
                              std::move (critical_left) );
            return;
        }
        
        // now degree of ucf_ad_domain is 2
        // the critical desc is a 221-desc
        
        auto && critical_221_desc = factor.Value_2 (critical_node);
        
        auto && Ww = B_prime.final_tree_with_node;
        auto && W = Ww.first;
        auto && w = Ww.second;
        
        Level_221_Desc critical_left (STATE::INVALID);
        // create a candidate to be assigned the first result of moving
        
        if (critical_direction == DIRECTION::LEFT
                ||
                B.IsContinuousTypeAtDomain() )
        {
            // the direction of ucf at Y is going left
            // operate with the final level-1 tree
            
            MoveToLeft (critical_221_desc,
                        critical_left,
                        T,
                        Q_prime,
                        q,
                        i,
                        W,
                        w,
                        DIRECTION::LEFT);
            // move to left under W,w and other parameters given
        }
        else
        {
        
            // the direction of ucf at Y is going down
            // operate with the final level-1 tree
            MoveToLeft (critical_221_desc,
                        critical_left,
                        T,
                        Q_prime,
                        q,
                        i,
                        W,
                        w,
                        DIRECTION::DOWN);
            // move to left under W,w and other parameters given
            // i is always going downwards
            // not included in the parameter of the MoveToLeft function
            //
        }
        
        if (critical_left.state == STATE::INVALID)
        {
            B_prime.state = STATE::INVALID;
            return;
        }
        auto && w_new = BaseUCF (critical_left, W);
        // the baseucf of critical_221_desc
        //      which is a (* * W+) desc
        
        PartialLevelOneTree Ww_new;
        
        if (w_new == nullptr)
        {
            Ww_new = PartialLevelOneTree (W);
        }
        else
        {
            Ww_new = PartialLevelOneTree (W, w_new);
        }
        
        auto extend_node_in_Y = node_in_Y->LastChild();
        
        while (extend_node_in_Y != nullptr)
        {
            if (  Match (
                        Ww_new,
                        Y.Partial (extend_node_in_Y)   )
               )
                break;
            extend_node_in_Y = extend_node_in_Y->Left();
        }
        
        B_prime.DiscontinuousTrim();
        B_prime.Extend_2 (Y,
                          extend_node_in_Y,
                          Ww_new,
                          std::move (critical_left) );
        return;
        
    }
    
    
    // now B_prime already exists, validated at transition point
    // want to move it left
    //
    
    auto && critical_direction = B.ucf_direction;
    auto && factor = B.factor;
    
    auto && node_in_Y = Y.MyNodeInDomain (B_prime.GetSequence() );
    
    auto && effective_length = B_prime.GetSequence().size();
    
    // later check if it properly extend the core part of C
    auto && effective_length_to_compare = B.GetSequence().size();
    
    
    
    if (B_prime.IsDiscontinuousType_Star (T, Q_prime) )
    {
        //B'_effective part can be end extended as (T,Q')-desc
        
        if (Degree (B_prime.ucf_at_domain_node) == DEGREE::ONE)
        {
            // degree 1
            
            auto && critical_21_desc = B_prime.UCF_21_Desc();
            
            Level_21_Desc critical_left (critical_21_desc);
            
            if (effective_length > effective_length_to_compare)
            {
                //no problem extending
                
                // move to the last child of critical 21 desc
                MoveToBKLeft (
                    critical_left,
                    T,
                    Q_prime.tree_1 );
            }
            else
            {
                // this means B' is B_effective_part extended by
                //  (C,-1), where C is the transitioning 221_Desc
                // so B'_effective_part = B_effective_part
                //
                // need to find another C'<C, good transitioning extension
                //
                auto && bound_in_B =  B.UCF_21_Desc();
                
                critical_left = critical_21_desc;
                
                MoveToLeft (bound_in_B,
                            critical_left,
                            T,
                            Q_prime.tree_1,
                            std::get<1> (q) );
            }
            
            if (critical_left.state == STATE::INVALID)
            {
                //squeezed out
                // no more
                B_prime.state = STATE::INVALID;
                return;
            }
            //found the good transition
            
            // now critical_left is the extention of B'_effective part,
            // need to find the node
            
            // note degree is never 0 as B' is *-disc type
            
            auto extend_node_in_Y = node_in_Y->LastChild();
            
            B_prime.DiscontinuousTrim();
            B_prime.Extend_1 (Y,
                              extend_node_in_Y,
                              std::move (critical_left) );
            return;
        }
        else
        {
            // need to find the biggest extension whth (W,w)
            // depraee 2
            //B'_effective part can be end extended as (T,Q')-desc
            
            auto && critical_221_desc = B_prime.UCF_221_Desc();
            
            Level_221_Desc critical_left (STATE::INVALID);
            
            if (effective_length > effective_length_to_compare)
            {
                //no problem extending
                
                if (B_prime.ucf_direction == DIRECTION::LEFT)
                {
                
                    auto && critical_parent = factor.Value_2 (Parent (B_prime.ucf_at_domain_node) );
                    
                    // move to the left with the same parent as critical 221 desc
                    
                    critical_left = critical_221_desc;
                    MoveToLeft (critical_parent,
                                critical_left,
                                T,
                                Q_prime,
                                B_prime.final_tree_with_node.first,
                                B_prime.final_tree_with_node.second);
                }
                else
                {
                    // move to the last child of critical 221 desc
                    MoveToLeft (critical_221_desc,
                                critical_left,
                                T,
                                Q_prime,
                                B_prime.final_tree_with_node.first,
                                B_prime.final_tree_with_node.second);
                }
            }
            else
            {
                // this means B' is B_effective_part extended by
                //  (C,-1), where C is the transitioning 221_Desc
                // so B'_effective_part = B_effective_part
                //
                // need to find another C'<C, good transitioning extension
                //
                auto && bound_in_B =  B.UCF_221_Desc();
                
                critical_left = critical_221_desc;
                
                if (B.ucf_direction == DIRECTION::LEFT
                   )
                {
                
                    MoveToLeft (bound_in_B,
                                critical_left,
                                T,
                                Q_prime,
                                q,
                                i,
                                B_prime.final_tree_with_node.first,
                                B_prime.final_tree_with_node.second,
                                DIRECTION::LEFT);
                }
                else
                {
                
                    MoveToLeft (bound_in_B,
                                critical_left,
                                T,
                                Q_prime,
                                q,
                                i,
                                B_prime.final_tree_with_node.first,
                                B_prime.final_tree_with_node.second,
                                DIRECTION::DOWN);
                }
                
                //found the good transition
            }
            
            if (critical_left.state == STATE::INVALID)
            {
                //squeezed out
                // no more
                B_prime.state = STATE::INVALID;
                return;
            }
            // now critical_left is the extention of B'_effective part,
            // need to find the node
            
            
            // now the node has degree 2
            
            // need to find the completion that matches (W+,w)
            
            auto && W = B_prime.final_tree_with_node.first;
            
            auto && w_new = BaseUCF (critical_left, W);
            // the base ucf of the critical left
            //  to decide the level-2 tree X , added entry, ucf of partial <=1 tree
            
            
            PartialLevelOneTree Ww_new;
            
            if (w_new == nullptr)
            {
                Ww_new = PartialLevelOneTree (W);
            }
            else
            {
                Ww_new = PartialLevelOneTree (W, w_new);
            }
            
            
            // need to find the biggest extension whth (W,w)
            
            auto extend_node_in_Y = node_in_Y->LastChild();
            
            while (extend_node_in_Y != nullptr)
            {
                if (  Match (
                            Ww_new,
                            Y.Partial (extend_node_in_Y)   )
                   )
                    break;
                extend_node_in_Y = extend_node_in_Y->Left();
            }
            
            B_prime.DiscontinuousTrim();
            B_prime.Extend_2 (Y,
                              extend_node_in_Y,
                              Ww_new,
                              std::move (critical_left) );
            return;
            
        }
    }
    else
    {
        //B'_effective part cannod be extended
        // must move
        
        if (effective_length == effective_length_to_compare)
        {
            B_prime.state = STATE::INVALID;
            return;
            // squeezed out
        }
        
        auto prev_node_in_Y = node_in_Y->Left();
        
        if (Y.Degree (node_in_Y->Parent() ) == DEGREE::TWO)
        {
            while (prev_node_in_Y != nullptr)
            {
                if (  Match (
                            Y.Partial (node_in_Y ),
                            Y.Partial (prev_node_in_Y)   )
                   )
                    break;
                prev_node_in_Y = prev_node_in_Y->Left();
            }
        }
        
        B_prime.DiscontinuousTrim();
        B_prime.MoveLastEntryInNode (Y,
                                     prev_node_in_Y);
        return;
    }
}


bool ShowUpInSignStar (const leq_2_Sequence & q,
                       const Level_21_Desc & D)
{
    if (std::get<0> (q) == DEGREE::ONE)
    {
        if ( D.Degree() == DEGREE::ONE &&
                D.sequence_1 == std::get<1> (q) )
            return true;
        else
        {
            return false;
        }
        
    }
    else
    {
        if ( D.Degree() == DEGREE::TWO &&
                D.sequence_2 == std::get<2> (q) )
            return true;
        return false;
    }
}


//given B, a (Y,T,(Q,q-,i)-desc
// Q' is the completion of (Q,q,i), q is the hanging node in Q'\Q
// B' is a candidate (Y,T,Q')-desc, produced by the MoveToLeftCandidate function, good at transition
//verify if B' is a (Y,T,Q)-desc
//
bool Validate (const Level_322_Desc &     B,
               const Level_322_Desc &     B_prime,
               const LevelThreeTree &    Y,
               const Level_leq_2_Tree &  T,
               const Level_leq_2_Tree &  Q_prime,
               const Level_leq_2_TreeNode & q,
               const DIRECTION i)
{
    if (B_prime.state == STATE::INVALID)
    {
        return false;
    }
    
    if (B_prime.IsDiscontinuousTypeAtDomain() )
    {
        return true;
    }
    
    auto && effective_length = B_prime.GetSequence().size();
    
    auto && effective_length_to_compare = B.GetSequence().size();
    
    if (effective_length > effective_length_to_compare)
    {
        return true;
    }
    
    //now B' is B_effective_part plus (C, -1)
    // we need to make sure of the well-behavior of C
    
    
    auto && last_node_in_B_prime = B_prime.LastNodeInDomain();
    
    if (Degree (last_node_in_B_prime) == DEGREE::ONE)
    {
        // deg of last node in B' is 1
        // it goes to a (T,Q1) desc
        
        
        auto && critical_desc = B_prime.GetFactor().Value_1 (last_node_in_B_prime);
        // the (T,Q1) desc to work with
        
        if (critical_desc.Degree() == DEGREE::ONE)
        {
            return false;
        }
        
        if (critical_desc.IsDiscontinuousTypeAtDomain() )
        {
            return true;
        }
        
        // now the critical desc is cont type at domain.
        // need to ensure the last entry is not q1
        auto && last_node = critical_desc.LastNodeInDomain();
        auto && last_value = critical_desc.GetFactor().Value (last_node);
        
        auto && q1 = Q_prime.tree_1.EntireEntry (std::get<1> (q) );
        
        if (last_value != q1 )
        {
            return true;
        }
        
        return false;
    }
    
    // now deg of las node in B' is 2
    // and B is cont at domain
    
    auto && W = B_prime.final_tree_with_node.first;
    
    auto && critical_desc = B_prime.GetFactor().Value_2 (last_node_in_B_prime);
    // the last 221 desc
    
    if ( critical_desc.IsDiscontinuousType (W) )
    {
        return true;
    }
    
    // now crit desc is W-cont type
    
    // we cneck if q has shown up before last of critical_desc
    
    auto && critical_factor = critical_desc.GetFactor();
    // the last 121 factor in 221 desc
    
    
    for (auto && i = critical_desc.enumeration.begin(); i != critical_desc.enumeration.end() - 1; ++i)
    {
        if ( ShowUpInSignStar (Q_prime.EntireEntry (q), critical_factor.Value (*i) ) )
        {
            return true;
        }
    }
    
    return false;
}


// given B, a (Y,T,Q)-desc
// B' , either invalid (standing for starting the computation) or a (B,T,Q')-desc whose restriction to (T,Q) is B,
// produce the left of B' whose restriction to (Y,T,Q) is still B
//
// Q' is the completion of (Q,q), q is the hanging node whose ucf in Q is going in the direction i
//
//  REMARK: B is a (Y,T, (Q,i,q-)-desc
//
//

void MoveToLeft (const Level_322_Desc & B,
                 Level_322_Desc & B_prime,
                 const LevelThreeTree & Y,
                 const Level_leq_2_Tree & T,
                 const Level_leq_2_Tree & Q_prime,
                 const Level_leq_2_TreeNode & q,
                 const DIRECTION & i)
{
    do
    {
        MoveToLeftCandidate (B, B_prime, Y, T, Q_prime, q, i);
        
        if (B_prime.state == STATE::INVALID)
        {
            return;
        }
        
        if (Validate (B, B_prime, Y, T , Q_prime, q, i) )
        {
            return;
        }
    }
    while (true);
}


// move B, a (Y,T,empty) desc (of "real " length 1) to the left
// they are embeddable into T
//
void MoveToLeftCandidate (Level_322_Desc & B,
                          const LevelThreeTree & Y,
                          const Level_leq_2_Tree & T)
{

    if (B.state == STATE::INVALID)
    {
        //look for the lasgest node. trivally embed into T
        auto && largest = Y.Root()->LastChild();
        if (largest == nullptr)
        {
            return;
        }
        B = Level_322_Desc (largest->LastEntry().first,
                            Y.Degree (largest) );
        return;
    }
    
    // now B is indeed a desc
    
    auto node_in_Y = Y.MyNodeInDomain (B.sequence);
    
    const Level_leq_2_Tree Q;
    // a trivail level<+2 tree
    
    // first, try to extend B
    //
    if (B.IsDiscontinuousType_Star (T, Q) )
    {
        // is extendable
        if (Degree (B.ucf_at_domain_node) == DEGREE::ONE)
        {
            // degree 1
            
            auto && critical_21_desc = B.UCF_21_Desc();
            // it has deg 1,
            // essentially a node in T1
            
            Level_21_Desc critical_left (critical_21_desc);
            
            MoveToBKLeft (critical_left,
                          T,
                          Q.tree_1
                         );
                         
            if (critical_left.state == STATE::INVALID)
            {
                B.state = STATE::INVALID;
                return;
            }
            auto extend_node_in_Y = node_in_Y->LastChild();
            
            B.DiscontinuousTrim();
            B.Extend_1 (Y,
                        extend_node_in_Y,
                        std::move (critical_left) );
            return;
        }
        
        else
        {
            auto && critical_221_desc = B.UCF_221_Desc();
            // it has deg 2,
            // essentially a node in T2
            
            Level_221_Desc critical_left (STATE::INVALID);
            
            if (B.ucf_direction == DIRECTION::LEFT
                    ||
                    B.IsContinuousTypeAtDomain() )
            {
                auto && critical_parent = B.factor.Value_2 (Parent (B.ucf_at_domain_node) );
                
                // move to the left with the same parent as critical 221 desc
                
                critical_left = critical_221_desc;
                MoveToLeft (critical_parent,
                            critical_left,
                            T,
                            Q,
                            B.final_tree_with_node.first,
                            B.final_tree_with_node.second);
            }
            else
            {
                MoveToLeft (critical_221_desc,
                            critical_left,
                            T,
                            Q,
                            B.final_tree_with_node.first,
                            B.final_tree_with_node.second);
            }
            
            if (critical_left.state == STATE::INVALID)
            {
                B.state = STATE::INVALID;
                return;
            }
            
            auto && W = B.final_tree_with_node.first;
            
            auto && w_new = BaseUCF (critical_left, W);
            // the base ucf of the critical left
            //  to decide the level-2 tree X , added entry, ucf of partial <=1 tree
            
            
            PartialLevelOneTree Ww_new;
            
            if (w_new == nullptr)
            {
                Ww_new = PartialLevelOneTree (W);
            }
            else
            {
                Ww_new = PartialLevelOneTree (W, w_new);
            }
            
            auto extend_node_in_Y = node_in_Y->LastChild();
            
            while (extend_node_in_Y != nullptr)
            {
                if (  Match (
                            Ww_new,
                            Y.Partial (extend_node_in_Y)   )
                   )
                    break;
                extend_node_in_Y = extend_node_in_Y->Left();
            }
            
            B.DiscontinuousTrim();
            B.Extend_2 (Y,
                        extend_node_in_Y,
                        Ww_new,
                        std::move (critical_left) );
            return;
        }
    }
    
    else
    {
        // must move
        
        
        auto prev_node_in_Y = node_in_Y->Left();
        
        if (node_in_Y->Length() > 1
                &&
                Y.Degree (node_in_Y->Parent() ) == DEGREE::TWO)
        {
            while (prev_node_in_Y != nullptr)
            {
                if (  Match (
                            Y.Partial (node_in_Y ),
                            Y.Partial (prev_node_in_Y)   )
                   )
                    break;
                prev_node_in_Y = prev_node_in_Y->Left();
            }
        }
        
        B.DiscontinuousTrim();
        B.MoveLastEntryInNode (Y,
                               prev_node_in_Y);
        return;
    }
}

//
//bool Validate (const Level_322_Desc &     B,
//               const LevelThreeTree &    Y,
//               const Level_leq_2_Tree &  T)
//{
//
//    cout << "+++++starting to validate length one desc +++++" << endl;
//
//
//    if (B.state == STATE::INVALID)
//    {
//        cout << "pos 1: false" << endl;
//        return false;
//    }
//
//    if (B.IsDiscontinuousTypeAtDomain() )
//    {
//        cout << "pos 2: true" << endl;
//        return true;
//    }
//
//    auto && effective_length = B.GetSequence().size();
//
//    auto && effective_length_to_compare = 1;
//
//    if (effective_length > effective_length_to_compare)
//    {
//        cout << "pos 3: true" << endl;
//        return true;
//    }
//
//    //now B' is B_effective_part plus (C, -1)
//    // we need to make sure of the well-behavior of C
//
//
//    auto && last_node_in_B_prime = B.LastNodeInDomain();
//
//    if (Degree (last_node_in_B_prime) == DEGREE::ONE)
//    {
//        // deg of last node in B' is 1
//        // it goes to a (T,Q1) desc
//
//        auto && critical_desc = B.GetFactor().Value_1 (last_node_in_B_prime);
//        // the (T,Q1) desc to work with
//
//        if (critical_desc.IsDiscontinuousTypeAtDomain() )
//        {
//            cout << "pos 4: true" << endl;
//            return true;
//        }
//
//
//        cout << "pos 6: false" << endl;
//
//        return false;
//    }
//
//    // now deg of las node in B' is 2
//    // and B is cont at domain
//
//    auto && W = B.final_tree_with_node.first;
//
//    auto && critical_desc = B.GetFactor().Value_2 (last_node_in_B_prime);
//    // the last 221 desc
//
//    if ( critical_desc.IsDiscontinuousType (W) )
//    {
//        cout << "pos 7: true" << endl;
//
//        return true;
//    }
//
//    // now crit desc is W-cont type
//
//    // we cneck if q has shown up before last of critical_desc
//
//
//    cout << "pos 9: false" << endl;
//    return false;
//}

bool Validate (const Level_322_Desc &     B,
               const LevelThreeTree &    Y,
               const Level_leq_2_Tree &  T)
{
    return true;
}

void MoveToLeft (Level_322_Desc & B,
                 const LevelThreeTree & Y,
                 const Level_leq_2_Tree & T)
{
    do
    {
        MoveToLeftCandidate (B, Y, T);
        
        if (B.state == STATE::INVALID)
        {
            return;
        }
        
        if (Validate (B, Y, T) )
        {
            return;
        }
    }
    while (true);
}


Level_332_FactorNode Parent (const Level_332_FactorNode & s)
{
    return Level_332_FactorNode (s.first->Parent(),
                                 s.second->Parent() );
}


Level_332_FactorNode Left (const Level_332_FactorNode & s)
{
    return Level_332_FactorNode (s.first->Left(),
                                 s.second->Left() );
}


class Level_332_Factor
{
public:

    string to_string (const Level_332_FactorNode & s) const
    {
        return ::to_string (domain.EntireEntryInDomain (s.first) );
    }
    
    string to_string (const unsigned & d = 0) const
    {
        string output;
        auto i = domain.Root()->FirstChild();
        auto j = factor.Root()->FirstChild();
        while (i != nullptr)
        {
            output += EmptyString (d);
            output += ::to_string (domain.EntireEntryInDomain (i) );
            
            output += " |---> the following 332 desc:\n";
            
            output += ::to_string (j->LastEntry().second, d + indent);
            output += "\n";
            i = domain.NextEnumerate (i);
            j = factor.NextEnumerate (j);
        }
        return output;
    }
    
    LevelThreeTree domain;
    FuncTree<SingleSequence, Level_322_Desc> factor;
    
    friend void swap (Level_332_Factor & f, Level_332_Factor & g)
    {
        swap (f.domain, g.domain);
        swap (f.factor, g.factor);
    }
    
    Level_332_Factor() = default;
    Level_332_Factor (const Level_332_Factor & pi) = default;
    Level_332_Factor (Level_332_Factor && pi)
    {
        swap (*this, pi);
    }
    Level_332_Factor& operator= (Level_332_Factor pi)
    {
        swap (*this, pi);
        return *this;
    }
    
    unsigned long Cardinality() const
    {
        return factor.Cardinality();
    }
    
    Level_332_FactorNode Root() const
    {
        return Level_332_FactorNode (domain.Root(),
                                     factor.Root() );
    }
    
    DEGREE Degree ( const Level_332_FactorNode & s)
    {
        return domain.Degree (s.first);
    }
    
    Level_332_FactorNode Add (const Level_332_FactorNode & s,
                              const DIRECTION & i,
                              PartialLevel_leq_2_Tree && Q,
                              const Level_322_Desc & B)
    {
        auto && a = ::Add (domain, s.first, i, std::move (Q) );
        auto && b = ::Add (factor, s.second, i, B);
        return Level_332_FactorNode (a, b);
    }
    
    // add a new node of degree 0 below root
    template <typename A>
    Level_332_FactorNode  Add_0 (const Level_332_FactorNode & s,
                                 A && B)
    {
        auto && d = domain.Add_0 (s.first);
        if (s.first->IsEmpty() )
        {
            auto && i = ::Add ( factor,
                                factor.Root(),
                                DIRECTION::DOWN,
                                std::forward<A> (B) );
            return Level_332_FactorNode (d, i);
        }
        auto && i = ::Add ( factor,
                            s.second,
                            DIRECTION::LEFT,
                            std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // add a  new node of degree 1 below root
    template <typename A>
    Level_332_FactorNode  Add_1 (const Level_332_FactorNode & s,
                                 A && B)
    {
        auto && d = domain.Add_1 (s.first);
        if (s.first->IsEmpty() )
        {
            auto && i = ::Add (factor,
                               factor.Root(),
                               DIRECTION::DOWN,
                               std::forward<A> (B) );
            return Level_332_FactorNode (d, i);
        }
        auto && i = ::Add (factor,
                           s.second,
                           DIRECTION::LEFT,
                           std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // add a  new node of degree 2 below root
    template <typename A>
    Level_332_FactorNode  Add_2 (const Level_332_FactorNode & s,
                                 A && B)
    {
        auto && d = domain.Add_2 (s.first);
        if (s.first->IsEmpty() )
        {
            auto && i = ::Add (factor,
                               factor.Root(),
                               DIRECTION::DOWN,
                               std::forward<A> (B) );
            return Level_332_FactorNode (d, i);
        }
        auto && i = ::Add (factor,
                           s.second,
                           DIRECTION::LEFT,
                           std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 1, so the value has a unique completion
    // the new node has degree 0
    // add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_10 (const Level_332_FactorNode & s,
                                  const DIRECTION & i3,
                                  A && B)
    {
        auto && d = domain.Add_10 (s.first, i3);
        auto && i = ::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    // s has degree 1, so the value has a unique completion
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_11 (const Level_332_FactorNode & s,
                                  const DIRECTION & i3,
                                  const SingleSequence & ucf_31,
                                  A && B)
    {
        auto && d = domain.Add_11 (s.first, i3, ucf_31);
        auto && i = ::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 1, so the value has a unique completion
    // add a new node in dhe diriciton i3
    // the hanging node  of the new partial level <=2 treegoes in the direction i2, with ucf ucf_32
    template <typename A>
    Level_332_FactorNode  Add_12 (const Level_332_FactorNode & s,
                                  const DIRECTION & i3,
                                  const DoubleSequence & ucf_32,
                                  const DIRECTION & i2,
                                  A && B)
    {
        auto && d = domain.Add_12 (s.first, i3, ucf_32, i2);
        auto && i =::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 0
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_200 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   A && B
                                  )
                                  
    {
        auto && d = domain.Add_200 (s.first, i3);
        auto && i =::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_201 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_31,
                                   A && B)
                                   
    {
        auto && d = domain.Add_201 (s.first, i3, ucf_31);
        auto && i =::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 2, with ucf ucf_32
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_202 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2,
                                   A && B
                                  )
                                  
    {
        auto && d = domain.Add_202 (s.first, i3, ucf_32, i2);
        auto && i =::Add (factor, s.second, i3,  std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    
    // s has degree 2,
    // need to complete the tree by making degree 1 in the hanging node
    //      in the level-2 part, with ucf ucf_21
    // the new node has degree 0
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_210 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   A && B)
    {
        auto && d = domain.Add_210 (s.first, i3, ucf_21);
        auto && i =::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 0 in the hanging node
    //      in the level-2 part
    // the new node has degree 1, with ucf ucf_31
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_211 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const  SingleSequence & ucf_31,
                                   A && B)
                                   
    {
        auto && d = domain.Add_211 (s.first, i3, ucf_21, ucf_31);
        auto && i =::Add (factor, s.second, i3,  std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    // s has degree 2,
    // need to complete the tree by making degree 1 in the hanging node
    //      in the level-2 part, with ucf ucf_21
    // the new node has degree 2, with direction i2 and ucf ucf_32
    //add a node , eithe child of s or an elder sister of s
    template <typename A>
    Level_332_FactorNode  Add_212 (const Level_332_FactorNode & s,
                                   const DIRECTION & i3,
                                   const SingleSequence & ucf_21,
                                   const DoubleSequence & ucf_32,
                                   const DIRECTION & i2,
                                   A && B
                                  )
    {
        auto && d = domain.Add_212 (s.first, i3, ucf_21, ucf_32, i2);
        auto && i =::Add (factor, s.second, i3, std::forward<A> (B) );
        return Level_332_FactorNode (d, i);
    }
    
    
    
    
    // s is a node in my factor, deg > 0, length > 0,
    //
    // Y,T is the trees to compute a tensor product
    //
    // in the middel of constructing Y \otimes T
    //
    // create children of n_tree
    //
    //
    void CreateChildren (const Level_332_FactorNode & s,
                         const LevelThreeTree & Y,
                         const Level_leq_2_Tree & T,
                         const Level_leq_2_Tree & Q_prime,
                         const Level_leq_2_TreeNode & q,
                         const DIRECTION i)
    {
        Level_322_Desc prev_desc (STATE::INVALID);
        
        MoveToLeft (factor.Value (s.second),
                    prev_desc,
                    Y,
                    T,
                    Q_prime,
                    q,
                    i
                   );
        if (prev_desc.state == STATE::INVALID)
        {
            return;
        }
        
        auto output = Add (s,
                           DIRECTION::DOWN,
                           BasePartialTree (prev_desc, Q_prime),
                           prev_desc);
                           
        while (true)
        {
            MoveToLeft (factor.Value (s.second),
                        prev_desc,
                        Y,
                        T,
                        Q_prime,
                        q,
                        i
                       );
            if (prev_desc.state == STATE::INVALID)
            {
                return;
            }
            
            output = Add (output,
                          DIRECTION::LEFT,
                          BasePartialTree (prev_desc, Q_prime),
                          prev_desc);
        }
    }
    
    
    
    
    
    // s is a node in my factor
    // Y,T is the trees to compute a tensor product
    //
    // in the middel of constructing Y \otimes T
    //
    // create children of s
    //
    Level_332_FactorNode CreateChildren (const Level_332_FactorNode & s,
                                         const LevelThreeTree & Y,
                                         const Level_leq_2_Tree & T)
    {
        if (s.first->IsEmpty() )
        {
            // create children of root
            Level_322_Desc prev_desc (STATE::INVALID);
            MoveToLeft (prev_desc, Y, T);
            
            if (prev_desc.state == STATE::INVALID)
            {
                return zeroLevel_332_FactorNode;
            }
            
            Level_leq_2_Tree Q;
            
            auto && new_ucf = BaseUCF (prev_desc, Q);
            
            auto d = std::get<0> (new_ucf.first);
            // the degree of the ucf
            
            Level_332_FactorNode current;
            
            if (d == DEGREE::ZERO)
            {
                current = Add_0 (s, prev_desc);
            }
            else if (d == DEGREE::ONE)
            {
                current = Add_1 (s, prev_desc);
            }
            else
            {
                current = Add_2 (s, prev_desc);
            }
            
            auto output = current;
            // record the last child down to output
            
            // now add elder sisters to current
            while (true)
            {
            
                MoveToLeft (prev_desc, Y, T);
                
                if (prev_desc.state == STATE::INVALID)
                {
                    // finished
                    return output;
                }
                auto && new_ucf = BaseUCF (prev_desc, Q);
                
                auto d = std::get<0> (new_ucf.first);
                // the degree of the ucf
                
                if (d == DEGREE::ZERO)
                {
                    current = Add_0 (current, prev_desc);
                }
                else if (d == DEGREE::ONE)
                {
                    current = Add_1 (current, prev_desc);
                }
                else
                {
                    current = Add_2 (current, prev_desc);
                }
            }
        }
        
        // now the node is nonempty
        
        // first, need to consider all the possible completions of
        //          the value at s
        
        if (Degree (s) == DEGREE::ZERO)
        {
            return zeroLevel_332_FactorNode;
            // not extendable!
        }
        
        
        if (Degree (s) == DEGREE::ONE)
        {
            auto && Q_prime_C = domain.Value (s.first).CompletionWithNode();
            auto && Q_prime = std::get<0> (Q_prime_C);
            auto && q = std::get<1> (Q_prime_C);
            auto && i = std::get<2> (Q_prime_C);
            CreateChildren (s,
                            Y,
                            T,
                            Q_prime,
                            q,
                            i);
            if (s.first->LastChild() != nullptr)
            {
                return Level_332_FactorNode (s.first->LastChild(),
                                             s.second->LastChild() );
            }
            
            return zeroLevel_332_FactorNode;
        }
        
        // now degree 2
        
        auto && P = domain.Value (s.first).final_tree_with_node.first;
        auto && p = domain.Value (s.first).final_tree_with_node.second;
        
        
        auto && Q_prime_C0 = domain.Value (s.first).CompletionWithNode();
        auto && Q_prime0 = std::get<0> (Q_prime_C0);
        auto && q0 = std::get<1> (Q_prime_C0);
        auto && i0 = std::get<2> (Q_prime_C0);
        
        CreateChildren (s,
                        Y,
                        T,
                        Q_prime0,
                        q0,
                        i0);
                        
                        
        for (auto && j = P.SmallestNode();
                j != P.Root();
                j = j->BKRight() )
        {
        
            auto && Q_prime_C = domain.Value (s.first).CompletionWithNode (P.EntireEntry (j) );
            
            
            auto && Q_prime = std::get<0> (Q_prime_C);
            auto && q = std::get<1> (Q_prime_C);
            auto && i = std::get<2> (Q_prime_C);
            
            CreateChildren (s,
                            Y,
                            T,
                            Q_prime,
                            q,
                            i);
                            
        }
        
        if (s.first->LastChild() != nullptr)
        {
            return Level_332_FactorNode (s.first->LastChild(),
                                         s.second->LastChild() );
        }
        return zeroLevel_332_FactorNode;
    }
};


Level_332_Factor TensorProduct (const LevelThreeTree Y, const Level_leq_2_Tree & T)
{
    Level_332_Factor rho;
    
    auto current  = rho.Root();
    
    auto temp = current;
    
    unsigned shiwan = 1;
    
    while (true)
    {
        if (rho.Cardinality() > shiwan * 100000)
        {
            cout << rho.Cardinality() << " added!" << endl;
            cout << "continue?" << endl;
            cin.get();
            shiwan = rho.Cardinality() / 100000 + 1;
        }
        
        temp = rho.CreateChildren (temp, Y, T);
        
        if (temp.first != nullptr)
        {
            current = temp;
            continue;
        }
        
        while (current.first != nullptr &&
                current.first->Left() == nullptr)
        {
            current = Parent (current);
        }
        if (current.first == nullptr)
        {
            // finished!!
            Flatten (rho.domain);
            Flatten (rho.factor);
            return rho;
        }
        current = Left (current);
        
        temp = current;
    }
}


string to_string (const Level_21_Desc & D,
                  const unsigned & d )
{
    return D.to_string (d);
}

string to_string (const Level_221_Desc & D,
                  const unsigned & d)
{
    return D.String221 (d);
}


string to_string (const Level_322_Desc & B,
                  const unsigned & d )
{
    return B.to_string (d);
}

string to_string (const leq_2_Sequence & s)
{
    if (std::get<0> (s) == DEGREE::ZERO)
    {
        return "[0, -1]";
    }
    if (std::get<0> (s) == DEGREE::ONE)
    {
        return "[1, " +
               to_string (std::get<1> (s) ) +
               "]";
    }
    
    return "[2, " +
           to_string (std::get<2> (s) ) +
           "]";
           
}

string Level_322_Desc::to_string (const unsigned d) const
{
    string s;
    
    s += EmptyString (d) + "node: " + ::to_string (sequence);
    
    if (IsContinuousTypeAtDomain() )
    {
        s.pop_back();
        s += " -1)";
    }
    
    s += "\n";
    
    s += EmptyString (d) + "level-222 factor map:\n";
    
    for (auto && i : enumeration)
    {
        auto && current_seq = factor.EntireEntryInDomain (i);
        s += EmptyString (d);
        s += ::to_string (current_seq);
        s += " |--> ";
        if (std::get<0> (current_seq) == DEGREE::ONE)
        {
            s += "the following level 21-desc\n";
            s += ::to_string (factor.Value_1 (i), d + indent );
        }
        else
        {
            s += "the following level 221-desc\n";
            s += ::to_string (factor.Value_2 (i), d + indent );
        }
    }
    return s;
}

string to_string (const LevelTwoTree & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const PartialLevel_leq_2_Tree & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const LevelThreeTree & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const LevelOneTree & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const Level_leq_2_Tree & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const Level_332_Factor & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}
string to_string (const Level_222_Factor & Q,
                  const unsigned & d)
{
    return Q.to_string (d);
}

vector<pair<int, int>> Count (const LevelTwoTree & Q)
{
    vector<pair<int, int>> output;
    for (auto && i = Q.Root();
            i != nullptr;
            i = i->BKLeft() )
    {
        if (output.size() <= i->Length() )
        {
            if (Q.Degree (i) == DEGREE::ZERO)
            {
                output.emplace_back (1, 0);
            }
            else
            {
                output.emplace_back (1, 1);
            }
        }
        else
        {
            if (Q.Degree (i) == DEGREE::ZERO)
            {
                ++ output[i->Length()].first;
            }
            else
            {
                ++ output[i->Length()].first;
                ++ output[i->Length()].second;
            }
        }
    }
    return output;
}

#endif // SHARP_H_INCLUDED

