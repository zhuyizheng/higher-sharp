from copy import deepcopy
from sets import Set
from itertools import combinations

indent  = 2

def printempty(d):
    for i in range(d):
        print(' '),
        
def stringempty(d):
    s = ""
    for i in range(d):
        s += " "
    return s

def MinusOne():
    return Node([-1])


class Node(object):
    ' a node in (*)^<omega'
    def __init__(self,entry = None):        #create a node in (*)^<omega
        if entry is None:
            entry = []
        self.entry = deepcopy(entry)        #by default, the entry is empty sequence


    def Enumerate (self):       # Enumerate the entry of the node
        for a in self.entry:
            yield a
    
    def IsInitialSegment(self, s):    # self is an initial segment of s
        
        if not isinstance(s, Node):
            return False
        if len(self.entry) > len(s.entry):
            return False
        for i in range(len(self.entry)):
            if not isinstance(self.entry[i], type(s.entry[i])):
                if not isinstance(s.entry[i], type(self.entry[i])):
                    return False
            if self.entry[i] != s.entry[i]:
                return False
        return True       
        
    def IsProperInitialSegment(self, s):    #self is a proper initial segment of s
  
        if not isinstance(s, Node):
            return False
        if len(self.entry) >= len(s.entry):
            return False
        for i in range(len(self.entry)):
            if not isinstance(self.entry[i], type(s.entry[i])):
                if not isinstance(s.entry[i], type(self.entry[i])):
                    return False
            if self.entry[i] != s.entry[i]:
                return False
        return True             
        
        
    def String(self):     #output the entry when it is a single node
        if self.IsMinusOne():
            o = '-' + '1'
        else:
            o = '('
            for j in self.entry:
                if type(j) is int:
                    o+=str(j)
                    o+=' '
                else:
                    o+=j.String()
            if self.IsNonEmpty():
                o = o [:-1]
            o+=')'
            o+=' '
        return o
        
    def Output(self):     #output the entry when is is a double node
        print(self.String()),
    

    def IsEmpty(self):
        return len(self.entry) == 0
    def IsNonEmpty(self):
        return not self.IsEmpty()
    
    def IsMinusOne(self):               # is it (-1)? 
        if self.Length() != 1:
            return False
        elif type(self.Entry(0)) is int:
            if self.Entry(0) == -1:
                return True
        else:
            return False
            
    def IsContinuousType(self):
        if self.IsEmpty():
            return False
        elif type(self.Entry(-1)) is int:
            if self.Entry(-1) == -1:
                return True
        else:
            return False
    def IsDiscontinuousType(self):
        return not  self.IsContinuousType()
    
    def Minus(self):        # outputs self^-
        return Node(self.entry[:-1])
        
    def Length(self):
        return len(self.entry)
        
    def Entry(self,k):
        if k>= self.Length():
            print ("This string is not that long!")
            return -2
        else:
            return self.entry[k]
    
    def LastEntry(self):
        return self.Entry(-1)
    
    def MakeEntry(self,s):
        self.entry = s

    def Append( self, a):   # append a to the end
        self.entry.append( deepcopy(a) )
        return self
        
    def AppendMinusOne( self):
        self.Append( -1 )
        return self
    
    def RestrictedTo(self, i):  #s restrcted to i
        return Node(self.entry[:i])
        
    def LengthOfIntersection(self,s):        #the length of common part of self and s
    
        for i in range ( min(self.Length(), s.Length()) ):
            if self.Entry(i) != s.Entry(i):
                return i
        return min(self.Length(), s.Length())
    
    def Intersection(self,s):        #the intersection of self and s
        return Node(s.entry[:self.LengthOfIntersection(s)])

    ####  reload operators    #####
    ####    by comparing the entries ###
    
    def __eq__(self,s):             #self == s
        if not isinstance(s, Node):
            return False
        if len(self.entry) != len(s.entry):
            return False
        for i in range(len(self.entry)):
            if not isinstance(self.entry[i], type(s.entry[i])):
                if not isinstance(s.entry[i], type(self.entry[i])):
                    return False
            if self.entry[i] != s.entry[i]:
                return False
        return True        
    def __ne__(self,s):             #self != s
        return not self==s
    def __le__(self,s):              #self<s, the BK order
        
        k = self.LengthOfIntersection(s)
        t = self.Intersection(s)
        
        if t == self:
            return False
        if t == s:
            return True
        if type(self.entry[k]) is int:
            if self.entry[k] == -1:
                return True
        if type(s.entry[k]) is int:
            if s.entry[k] == -1:
                return False
        return self.entry[k]<s.entry[k]
    def __lt__(self,s):             #self<=s, the BK order
        return self<=s and self != s
    def __gt__(self,s):             #self > s
        return not self <= s
    def __ge__(self,s):             #self >= s
        return not self < s

class TreeNode(Node):
    ' a node in a tree'
    
    def __init__(self,entry = []):        #create a node in omega^<omega
        super(TreeNode, self).__init__(entry)

        self.parent = None
        self.number_of_children = 0
        self.first_child = None
        self.last_child = None
        self.left = None
        self.right = None
        self.BKleft = None
        self.BKright = None
        
        self.immediate_extensions = None #when double tree, the set of s such that self+[s] is in the tree

    def Degree(self):       # is it a node in a single tree or double tree?
        if self.immediate_extensions is None:
            return 1
        else:
            return 2
    
    def IsLastBitLeftMost(self):    #is the last bit leftmost?
        return self.left is None
    def IsLastBitRightMost(self):    #is the last bit right most?
        return self.right is None
    def IsBKLeftMost(self):            #is it BK left most?
        return self.BKleft is None


    def HasChild (self):            #does it have children?
        return self.number_of_children > 0
    def IsTerminal (self):
        return not self.HasChild()    
     
            
    def MyChild (self, s):            #output my child whose last entry is s
        
        current = self.first_child
        for i in range (self.number_of_children):
            if current.LastEntry() == s:
                return current
            else:
                current = current.right
        return None
        
    def MakeNewChildBelow(self, s, new):
        #make "new" a child below s

        if self.Degree() == 2:   #double tree
            if s.IsNonEmpty():
                if not self.immediate_extensions.ContainsElement(s):
                    print ("s is nonempty and not the last entry in the immediate extension! Impossible to add a child!")
                    return None
            
            self.number_of_children += 1
            #number_of_children + 1
            
            single = self.immediate_extensions.AddNodeBelowNextLevel(s)
            #single is the extension of s to be added
            
            if s.IsNonEmpty():
                current = self.MyChild(s)
            else:
                current = self
            #current is the BK next of the new node
            
            new.immediate_extensions = LevelOneTree()
            new.entry = self.entry + deepcopy([single])
            new.parent = self
            #create a new node whose entry extends by s, parent point to self
            
            if current.IsNonEmpty():
                tempcurrentBKleft = current.BKleft
                if (not current.IsBKLeftMost()):
                                                    #if current is not BKleftmost,
                                                    #its left and itself has new in between
                    new.BKleft = current.BKleft     #assign the left of new and vice versa
                    current.BKleft.BKright = new
                    
                                                    #otherwise, nothing to do
                    
                new.BKright = current       #the right of the new node must be current
                current.BKleft = new        #assign them under all cases
            elif self.number_of_children > 1:
                new.BKleft = current.last_child 
                current.last_child.BKright = new
                new.BKright = self
                self.BKleft = new
            else:
                new.BKright = self
                self.BKleft = new
                
            #finished assign the BK order
            
            if self.number_of_children == 1:
                
                self.first_child = new
                self.last_child = new
                return new
            #assign the children when it is the first child
            
            if single == self.immediate_extensions.SmallestNode():
                
                new.right = self.first_child
                self.first_child.left = new
                self.first_child = new
            #assign the first children and siblings when it is before the smallest child
                
            elif s.IsNonEmpty():
                
                new.left = tempcurrentBKleft
                new.right = current
                current.left.right = new
                current.left = new
            #assign the siblings when it is in between two children
            
            else:
                new.left = self.last_child
                self.last_child.right = new
                self.last_child = new
            #assign the last children and siblings when it is after the greatest child    
                
            return new
            
        else:       #single tree
                    
            new.entry = self.entry + [deepcopy(self.number_of_children)]
            
            new.parent = self
            
            self.number_of_children +=1
            
            if self.IsNonEmpty():
                new.BKright = self        
                
                if not self.IsBKLeftMost():
                    new.BKleft = self.BKleft
                    self.BKleft.BKright = new
                
                self.BKleft = new
            
            elif self.number_of_children > 1:
                new.BKleft = self.last_child
                self.last_child.BKright = new
                new.BKright = self 
                self.BKleft = new
            else:
                new.BKright = self 
                self.BKleft = new
            
            
            if self.number_of_children == 1:
                self.first_child = new
                self.last_child = new
            
            else:
                self.last_child.right = new
                new.left = self.last_child
            
            self.last_child = new
            
            return new


    def AddChildBelow (self, s):            #add a child below the single node s, returns the new child
        # if s is None, this means self is a single tree
        # if s is a node, this means self is a double tree
        
        new = TreeNode()
        self.MakeNewChildBelow(s, new)
        return new

    def AddChildren (self, P):          
        #when P is a level-1 tree: 
        #       the tree is double. add children that forms a level-1 tree P, only when it has no children, and returns the first child
        #when k=P is int:
        #       the tree is single. add k children
        
        if type(P) is not int:  #double tree
            if self.HasChild():
                print("This double node already has children!")
                return None
            
            if P.IsTrivial():
                return None

            for a in P.Enumerate():
                self.AddChildBelow ( a.Minus() )
                
            return self.first_child
        
        else:       #single tree
            k = P
            if k == 0:
                return None
                
            new = self.AddChild()
            
            for i in range (1, k):
                self.AddChild()
                
            return new
                    
    
class Tree(object):
    'A nonempty tree, but -1 and other negative numbers are never allowed anywhere in the entry'
    
    def __init__(self):
        self.cardinality = 1        #the default tree has card 1, only root
        self.root = TreeNode([])
    
    def Degree(self):
        return self.root.Degree()
    
    def Cardinality(self):
        return self.cardinality
        
    def SmallestNode(self):
        current = self.root
        while current.HasChild():
            current = current.first_child
        return current
    
    def IsSubtree (self, T):        #is self a subtree of T?
                
        for s in self.Enumerate():
            if not T.ContainsElement(s):
                return False
        return True
            
    def __eq__(self,T):
        if not isinstance(T, Tree):
            return False
        return self.IsSubtree(T) and T.IsSubtree(self)
    def __ne__(self,T):
        return not self == T
    
    def IsTrivial(self):
        return self.root.IsTerminal()
    def IsNonTrivial(self):
        return not self.IsTrivial()
    
    def ContainsElement (self, s):   #does it contain the element coded in the node s 
        
        if s.IsEmpty():
            return True
        if self.IsTrivial():
            return False
        
        #compare them bit by bit
        
        current = self.root
        for i in range(s.Length()):
            if type(s.Entry(i)) is int:
                if current.immediate_extensions is not None:
                    return False
                if s.Entry(i) < 0:
                    return False
                if current.number_of_children <= s.Entry(i):
                    return False
            else:
                if current.immediate_extensions is None:
                    return False
                if not current.immediate_extensions.ContainsElement(s.Entry(i)):
                    return False
            
            current = current.MyChild(s.Entry(i))
        
        return True
    
    def MyNode (self, s):    #return the node in me pointing to s
        if not self.ContainsElement(s):
            print("This node is not in the tree!")
            return None
        current = self.root
        for i in range(s.Length()):
            current = current.MyChild(s.Entry(i))
        return current

    def NodeOnRight (self,s):   #return the least node in me which is >_BK s
        
        current = self.SmallestNode()
        
        while current is not None:
            if current > s:
                return current
            current = current.BKright
            
        print("There is no node on the right in this tree")
        return None
        
    def NodeOnLeft (self,s):   #return the least node in me which is <_BK s
        
        current = self.root
        
        while current is not None:
            if current < s:
                return current
            current = current.BKleft

        print("There is no node on the left in this single tree")
        return None


    def AddNodeBelowSameLevel (self,s):  
        #add a node below s at the rightmost of same level, returns the new node in the tree
        # applied only to double trees
        
        new = TreeNode()
        new = self.MakeNewNodeBelowSameLevel(s,new)
        return new

    def AddNodeBelowNextLevel (self,s):  
        #add a node below s at the rightmost of next level, returns the new node in the tree
        new = TreeNode()
        new = self.MakeNewNodeBelowNextLevel(s,new)
        return new
        
    def MakeNewNodeBelowSameLevel (self, s, new):    #makes "new" the new node below s, same level at the rightmost

        current = self.MyNode(s.Minus())
        
        self.cardinality += 1
        
        current.MakeNewChildBelow(s.LastEntry(),  new)
        return new

    def MakeNewNodeBelowNextLevel (self, s, new):    #makes "new" the new node below s, at the rightmost
        
        if self.Degree() == 1:
            if s.IsEmpty():             # if empty sequence, add it
                
                self.cardinality += 1
                    
                self.root.MakeNewChildBelow(None, new)
                    
                return new
                
            if not self.ContainsElement(s): #if not empty sequence, it must be an element of s in the first place
                
                print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
                
                return None
                
            current = self.MyNode(s)
            
            self.cardinality += 1
            
            new = current.MakeNewChildBelow(None, new)
            
            return new
            
        else:
            if s.IsEmpty():             # if empty sequence, add it
                
                self.cardinality += 1
                
                new = self.root.MakeNewChildBelow(TreeNode(), new)
                return new
                
            if not self.ContainsElement(s): #if not empty sequence, it must be an element of s in the first place
                
                print ("This double sequence is not empty, not in the tree. Impossible to add a node below in the double tree")
                
                return None
                
            current = self.MyNode(s)
            
            self.cardinality += 1
            
            new = current.MakeNewChildBelow(TreeNode(), new)
            return new
            
    def AddNodesBelow (self,s, k): 
        #when degree 1: add k nodes below s, returns the first new node in the tree
        #when degree 2: P = k is a level-1 tree. add nodes below s that forms P, returns the first new node
        
        if self.Degree() == 1:
            if k==0:
                return None
            
            new = self.AddNodeBelowNextLevel (s)
            
            for i in range (1,k):
                
                self.AddNodeBelowNextLevel(s)
                
            return new
        else:
            P = k 

            if P.IsTrivial():
                return None
            
            if s.IsEmpty():
                
                self.cardinality += P.Cardinality()
                
                return self.root.AddChildren(P)
            
            if not self.ContainsElement(s): #if not empty sequence, it must be an element of s in the first place
                
                print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
                
                return None
                
            current = self.MyNode(s)
                    
            self.cardinality = self.cardinality + P.Cardinality()
                
            return current.AddChildren(P)

  
    def BKEnumerate(self):      #enumerate the nodes in the BK order
        
        current = self.SmallestNode()
        
        while current is not None:
            yield current
            current = current.BKright
            
        
    def Enumerate(self):   #enumerate the nodes in the dictionary order, NOT IN THE BK ORDER!
        
        yield self.root
        
        if self.IsTrivial():
            return
            
        current = self.root.first_child
        
        while current.IsNonEmpty():
            
            yield current
            
            if current.HasChild():
                current = current.first_child
                
            else:
                while current.IsNonEmpty() and current.IsLastBitRightMost():
                    current = current.parent
                if current.IsEmpty():
                    return
                else:
                    current = current.right

    def Rank(self, s):            # the BK-rank of s in the tree 
        
        if not self.ContainsElement(s):
            print("This node doesn't belong to the tree! No rank!")
            return None
            
        i = 0
        current = self.SmallestNode()
        
        while ( current != s):
            i += 1
            current = current.BKright
        return i
        
    def InputDouble(self, d):      #input the doubletree on the screen
        
        self.cardinality = 1
        
        current = self.root
        self.root.immediate_extensions = LevelOneTree()
        
        while True:
            
            for i in range(d):
                print(" "),
            
            print ("Input the double tree, immediate successors of"), 
            current.Output(),
            print ("forms a level-1 tree:")
            
            K = LevelOneTree()
            K.Input(d+indent)
            
            if K.IsTrivial():
                
                if current.IsEmpty():
                    
                    return
                    
                while current.IsLastBitRightMost():
                    
                    current = current.parent
                    
                    if current.IsEmpty():
                    
                        return
                        
                current = current.right
                
            else:
                    
                self.AddNodesBelow(current,K)
                    
                current = current.first_child



class LevelOneTree (Tree):
    'a level-1 tree'

    def __init__(self):
        super(LevelOneTree, self).__init__()
        self.cardinality = 0        #the root is not in the level-1 tree
        
    def IsRegular(self):
        return self.root.number_of_children <= 1
        
    def SmallestNode(self):
        if self.IsNonTrivial():
            return super(LevelOneTree, self).SmallestNode()
    def ContainsElement(self,s):
        return s.IsNonEmpty() and super(LevelOneTree,self).ContainsElement(s)
    def Enumerate(self):
        
        if self.IsTrivial():
            return
            
        current = self.root.first_child
        
        while current.IsNonEmpty():
            
            yield current
            
            if current.HasChild():
                current = current.first_child
                
            else:
                while current.IsNonEmpty() and current.IsLastBitRightMost():
                    current = current.parent
                if current.IsEmpty():
                    return
                else:
                    current = current.right
                    
    def BKEnumerate(self):
        
        current = self.SmallestNode()
        
        while current.IsNonEmpty():
            yield current
            current = current.BKright
            

    def Input(self, d):      #input the tree on the screen
        self.cardinality = 0
        
        current = self.root
        
        printempty(d)
        print("Input the level-1 tree:")
                
        while True:
    
            printempty(d+indent)
            
            print ("How many immediate successors of"), 
            current.Output() 
            print ("?  "),
                    
            
            k = input()
                    
            if k == 0:
                if current.IsEmpty():
                    printempty(d)
                    print ("Level-1 tree input complete!")
                    return
                    
                while current.IsLastBitRightMost():
                    current = current.parent
                    if current.IsEmpty():
                        printempty(d)
                        print ("Level-1 tree input complete!")
                        return
                        
                current = current.right
                
            else:
                    
                self.AddNodesBelow(current,k)
                current = current.first_child
    

class PartialLevelOneTree(object):
    
    def __init__(self, tree = None, node = None):     #by default, assign it the empty tree and the node with entry (0)
        
        if tree is None:
            tree = LevelOneTree()
            node = TreeNode ([0])
        self.tree = deepcopy(tree)
        self.node = deepcopy(node)
        
    def IsPartialLevelOneTree(self):        # is it a partial level-1 tree?
        if self.node.Length() <=1:
            if self.tree.IsTrivial() and self.node.entry == [0]:
                return True
            return False
        if not self.tree.IsRegular():
            return False
        if self.tree.ContainsElement(self.node):
            return False
        if not self.tree.ContainsElement(self.node.Minus()):
            return False
        return self.tree.MyNode(self.node.Minus()).number_of_children == self.node.LastEntry()
        
    def IsTrivial(self):
        return self.tree.IsTrivial()

    def Degree (self):
        if self.node.IsMinusOne():
            return 0
        return 1
    
    def Tree(self):
        return self.tree
    def Node(self):
        return self.node
        
    def Completion(self):
        if self.Degree()==0:
            print("This partial level <=1 tree is of degree 0, no completion!")
            return None
        P = deepcopy(self.tree)
        p = deepcopy(self.node)
        P.AddNodeBelowNextLevel (p.Minus())
        return P
    
    def Cardinality(self):
        return self.tree.Cardinality() + 1
        
    def UniformCofinality(self):
        if self.Degree() == 0:
            return MinusOne()
        return self.node.Minus()

    def __eq__(self,s):
        return self.tree == s.tree and self.node == s.node
    def __ne__(self,s):
        return not self == s
    
    def IsPartialSubtree (self,P):
        if self.Degree() == 0:
            return False
        return self.Completion().IsSubtree(P)
    
    def IsContinuousType (self):
        return self.node.IsContinuousType()
    def IsDiscontinuousType(self):
        return not self.IsContinuousType()

        
class FuncNode(TreeNode):
    'A unit of a map from a tree'
    
    def __init__(self, entry = None, value = None):
        
        if entry is None:
            entry = []
        super(FuncNode,self).__init__(entry)
        self.value = value      #the value of the function at entry
        
    def Variable(self):
        return self.entry
    def Value(self):
        return self.value
        
    def MakeValue(self, value):
        self.value = value
        
    def AddChildBelowWithValue (self,s, y):            
        #add a child below s, with value y, returns the node of child
        
        new = FuncNode()
        self.MakeNewChildBelow( s, new)
        new.value = y
    
    def __eq__(self,s):             #self == s at the pair (variable,value)
        if not isinstance(s, FuncNode):
            return False
        if not isinstance(self.entry, type(s.entry)):
            if not isinstance(s.entry, type(self.entry)):
                return False
        if not isinstance(self.value, type(s.value)):
            if not isinstance(s.value, type(self.value)):
                return False
        return self.entry == s.entry and self.value == s.value
    def __ne__(self,s):             #self != s
        return not self==s

class FuncTree(Tree):
    'A template for nonempty functions from a tree'
    
    def __init__(self, root_value = None):
        super(FuncTree,self).__init__()
        self.root = FuncNode()
        self.root.value = root_value
    
    def AddNodeBelowWithValueSameLevel(self, s, y):
        
        new = FuncNode()
        new = self.MakeNewNodeBelowSameLevel(s,new)
        new.value = y
        return new
        
    def AddNodeBelowWithValueNextLevel(self, s, y):
        
        new = FuncNode()
        new = self.MakeNewNodeBelowNextLevel(s,new)
        new.value = y
        return new
    
    def ContainsInDomain(self,s):
        return self.ContainsElement(s)
    
    def CopyIntoDomain(self, Q):    #starting from empty map, copy the tree Q into its domain

        self.cardinality = Q.cardinality 
        
        record = [[Q.root,  self.root]]
        
        for q in Q.Enumerate():
            new = FuncNode()
            new.entry = q.entry
            record.append([q, new])
        for [q1, s1] in record:
            for [q2, s2] in record:
                if q1.parent is not None:
                    if q1.parent == q2:
                        s1.parent = s2
                if q1.left is not None:
                    if q1.left == q2:
                        s1.left = s2
                if q1.right is not None:
                    if q1.right == q2:
                        s1.right = s2
                if q1.BKright is not None:
                    if q1.BKright == q2:
                        s1.BKright = s2
                if q1.BKleft is not None:
                    if q1.BKleft == q2:
                        s1.BKleft = s2
                if q1.first_child is not None:
                    if q1.first_child == q2:
                        s1.first_child = s2
                if q1.last_child is not None:
                    if q1.last_child == q2:
                        s1.last_child = s2
        for [q, s] in record:
            s.number_of_children = q.number_of_children
            s.immediate_extensions = q.immediate_extensions

        return
    
    def EnumerateDomain(self):
        for a in self.Enumerate():
            yield a
        return
    def BKEnumerateDomain(self):
        for a in self.BKEnumerate():
            yield a
        return
        
    def EnumerateWithValue(self):       #never used??
        
        e = self.EnumerateDomain()
        f = []
        for p in e:
            f.append ( [ p, self.Value(p)])
        return f
    
    def IsSubfunction (self, T):        #is self a subfunction of T?
        
        if not isinstance(T, FuncTree):
            return False
        if not self.IsSubtree(T):
            return False
        for s in self.EnumerateDomain():
            if s != T.MyNode(s):
                return False
        return True
             
    def __eq__(self,T):
        if not isinstance(T, FuncTree):
            return False
        return self.IsSubfunction(T) and T.IsSubfunction(self)
        
    def __ne__(self,T):
        return not self == T
    
    def IsTrivial(self):        #is the tree trivial, i.e. nothing extending emptyset?
        # just equivalent to the IsEmpty definition
        return self.root.number_of_children == 0
    def IsNonTrivial(self):
        return not self.IsTrivial()
    
    def ContainsElementWithValue (self, s, y):   #is s NONEMPTY AND a member of T and y is the value of s? (by default, emptyset is not in any tree) 
        
        if s.IsEmpty():
            return self.root.value == y
        if self.IsTrivial():
            return False
                        
        #compare them bit by bit
        
        current = self.root
        
        for i in range(s.Length()):
            
            current = current.first_child
            
            while not current.IsLastBitRightMost():
                
                if current.entry == s and current.value == y:
                    break
                current = current.right
                    
            if not (current.entry == s and current.value == y):
                return False
        
        return True
    

    
    def MyNodeAtDomain (self, s):    #return the node in me pointing to s
        return self.MyNode(s)
    
    def Value(self, s):         # get the value at s
        return self.MyNodeAtDomain(s).Value()

    def Preimage (self, y):     # get the first preimage of y
        current = self.SmallestNode()
        while current is not None:
            if self.Value(current) == y:
                return current
            current = current.BKright

    def MakeValue(self,s,y):          #make the value at s y
        self.MyNodeAtDomain(s).value = y
 

    def ContainsInRange(self, s):   #does s belong to the range?
            
        current = self.root()
        while current is not None: 
            if isinstance(s, type(self.Value (current))) or isinstance(self.Value (current), type(s)):
                if s == self.Value (current) :
                    return True
            current = current.BKleft
        return False
    
    def RestrictedTo(self,P):   # the map restricted to P
        temp = LevelOneFactor()
        temp.CopyIntoDomain(P)
        temp.root.value = self.root.value
        for p in temp.BKEnumerate():
            p.MakeValue( self.Value (p))
        return temp

def MakePartialLevelOneTree (P):            ## makes a list of partial level-1 trees whose tree component is P
    
    if not P.IsRegular():
        print("This level-1 tree is not regular. Cannot extend to a partial level-1 tree.")
        return None
    
    if P.IsTrivial():
        
        return [PartialLevelOneTree()]
        
    else:
        
        t = [PartialLevelOneTree( P, MinusOne()) ]
        
        for ee in P.Enumerate():
            
            t.append( PartialLevelOneTree( P, TreeNode( ee.entry + [ee.number_of_children] )  ) )
        
        return t

def EnumerateNodesOfPartialLevelOneTree(P):    # makes a list of the nodes of partial level-1 trees whose component is P
    
    if P.IsTrivial():
        return [MinusOne()]
    
    t = MakePartialLevelOneTree(P)
    u = []
    for ee in t:
        u.append(ee.node)
    
    return u



class LevelTwoTree(FuncTree):
    'a level-2 tree'

    def __init__(self):
        
        super(LevelTwoTree,self).__init__( PartialLevelOneTree() )
        #the default value at empty is the trivial partial level <=1 tree, (empty, (0))
        self.cardinality = 1
        self.root.immediate_extensions = LevelOneTree()
        
    def Value(self, s):
        if s.IsNonEmpty():
            return super(LevelTwoTree,self).Value(s)
        return self.root.value
    
    def Input(self,d):
        
        printempty(d)
        print ("Input the level-2 tree. Its domain is a double tree:")
        
        Q = Tree()
        Q.InputDouble(d+indent) 
        self.CopyIntoDomain(Q) 
                
        e = self.EnumerateDomain()
        
        for ee in self.EnumerateDomain():
            
            if ee.IsNonEmpty():
                
                partial = self.Value(ee.Minus())
                completion = partial.Completion()
                partial_extend = MakePartialLevelOneTree(completion)
                partial_extend_node = EnumerateNodesOfPartialLevelOneTree(completion)
                
                printempty(d)
                print "Possible values of the node component of this level-2 tree at", 
                ee.Output() 
                print ":"
                

                for i in range(len(partial_extend_node)):
                    printempty(d+indent)
                    print i+1, ". ", 
                    partial_extend_node[i].Output()
                    print " "
                printempty(d)
                k = input("which one?  ")
                
                self.MakeValue(ee, partial_extend[k-1] )
                
                printempty(d)
                print("Level-2 tree input complete!")

        
    def ContainsInDomainStar(self,s):       #does dom^*(self) contain the double node s?
        if self.ContainsInDomain(s):
            return True
        if s.IsContinuousType() and self.ContainsElement(s.Minus()):
            return True
        return False
    
    def GetPartialLevelOneTower(self,s):    #outputs the Q[s], the partial level <=1 tower of discontinuous type, for s in dom^*(Q)
            
        if self.ContainsInDomain(s):        #when s in dom(Q), the output is of discontinous type
            t = PartialLevelOneTower()
            for i in range(1, s.Length()+1):
                t.AppendPartialTree( self.Value( s.RestrictedTo(i)) )  
            return t
            
        if self.ContainsInDomainStar(s):    #when s in dom*(Q)\dom(Q), the output is of continous type
            t = self.GetPartialLevelOneTower( s.Minus())
            t.AppendCompletion()
            return t
            
    def GetLevelTwoDescription(self,s):     #outputs the Q-description ( s, Q[s])
        
        return LevelTwoDescription( s.entry, self.GetPartialLevelOneTower(s) )
            
    
class PartialLevelOneTower:
    'partial level <=1 tower'
    #we don't define potential partial level <=1 tower, as it is 
    #easily coded in a partial level <=1 tower
    
    def __init__(self, tree_sequence = None, node_sequence = None):
    #
    # by default, it constructs ([empty],[(0)]), which is Q([0]) for any level-2 tree Q
    #
        if tree_sequence is None:
            tree_sequence = [LevelOneTree()]
            node_sequence = [TreeNode([0])]
        self.tree_sequence = deepcopy(tree_sequence)
        self.node_sequence = deepcopy(node_sequence)
    
    def IsTrivial(self):
        return len(self.tree_sequence)==1
    
    def IsContinuousType(self):
        return len(self.tree_sequence) == len(self.node_sequence)+1
    
    def IsDiscontinuousType(self):
        return len(self.tree_sequence) == len(self.node_sequence)
    
    def LengthOfTreeSequence(self):
        return len(self.tree_sequence)
    def LengthOfNodeSequence(self):
        return len(self.node_sequence)
    
    def TreeEntry(self, i):         #the i-th tree in its tree sequence
        if i >= self.LengthOfTreeSequence():
            print("This partial level-1 tower does not have so many trees!")
            return
        return self.tree_sequence[i]
        
    def NodeEntry(self, i):         #the i-th node in its node sequence
        if i >= self.LengthOfNodeSequence():
            print("This partial level-1 tower does not have so many node!")
            return
        return self.node_sequence[i]
    
    def NodeSequence(self):
        return self.node_sequence
    def TreeSequence(self):
        return self.tree_sequence   
        
    def Signature(self):                    #signature
        if self.IsDiscontinuousType():
            return self.node_sequence [:-1]
        else:
            return self.node_sequence
    
    def Tree(self):                 # the last tree in its tree sequence
        return self.tree_sequence[-1]
        

    
    def LastNodeWhenContinuous(self):
        if self.IsContinuousType:
            return self.node_sequence[-1]
        else:
            return None
    def LastPartialTreeWhenDiscontinuous(self):
        if self.IsDiscontinuousType:
            return PartialLevelOneTree( self.tree_sequence[-1], self.node_sequence[-1] )
        else:
            return None

    def UniformCofinality(self):    #uniform cofinality of the partial tree
        if self.IsDiscontinuousType():
            return self.LastPartialTreeWhenDiscontinuous().UniformCofinality()
        else:
            return self.LastNodeWhenContinuous()
    
    def Completion(self):           #the completion when discontinuous type
        if self.IsDiscontinuousType():
            return self.LastPartialTreeWhenDiscontinuous().Completion()
            
    def AppendCompletion(self):      #append the comletion to make it continous type
        self.tree_sequence.append( self.Completion())
        return self
    
    def AppendPartialTree(self, P): #append a partial tree to discontinuous type. The result remains discontinous type
        if self.IsDiscontinuousType():
            self.tree_sequence.append( P.tree )
            self.node_sequence.append( P.node )
        return self
    
    def AppendNode(self, p):        #append a node to a continuous type. makes it discontinuous type
        self.node_sequence.append( p )
        return self
    
    def __eq__(self, PP):
        return self.tree_sequence == PP.tree_sequence and self.node_sequence == PP.node_sequence
        
    def __ne__(self,PP):
        return not self == PP
    
    
    def RestrictedTo(self,i):       # the tower restricted to i has length i+1!
    # in particular, restricted to 0 has length 1, consisting of Q(0)
        return PartialLevelOneTower(self.tree_sequence[:i+1], self.node_sequence[:i+1])

def Decapped(PP):             # when continuous type, outputs the one without the last tree
    return PartialLevelOneTower(   PP.tree_sequence[:-1]  , PP.node_sequence)

def Completed(PP):            #when discontinous type, outputs the one with a completion attached
    return PartialLevelOneTower(   PP.tree_sequence + [ PP.Completion()]  , PP.node_sequence)
    
#    def __lt__(self,PP):        #self is a proper initial segment of PP
            
class LevelOneFactor (FuncTree):
    'level-1 factoring map'
    
    def __init__(self):
        super(LevelOneFactor,self).__init__( Node([]) )
        
    def IsFactor(self):     # is it a level-1 factoring map?
        current = self.SmallestNode()
        while (current.BKright is not None):
            if self.Value(current) >= self.Value(current.BKright):
                return False
            current = current.BKright
        return True
    
    def Domain(self):   # the domain of self
        P = deepcopy(self)
        P.cardinality -= 1
        return P
        
    def IsFactorInto(self, W):      # is it a level-1 factoring map into W?
        if self.IsTrivial():
            return True
        if not self.IsFactor():
            return False
        current = self.root.BKleft
        while current is not None:
            if not W.ContainsElement(self.Value(current)):
                return False
            current = current.BKleft
        return True
    
    def CopyIntoDomain(self, Q):
        super(LevelOneFactor, self).CopyIntoDomain(Q)
        self.cardinality += 1
    
class Level_leq_2_Node (object):     
    'a node of the form (0,-1), or (1,q), q in omega^<omega, or (2,q), q in omega^{omega^<omega}'
    
    def __init__(self, degree = None, node = None):
        if degree is None:
            degree = 2
            node = FuncNode()
        self.degree = deepcopy(degree)
        self.node = deepcopy(node)
    
    def Degree(self):
        return self.degree
        
    def Node(self):
        return self.node
        
    def __eq__(self,q):
        return self.degree == q.degree and self.node == q.node
    def __ne__(self,q):
        return not self == q
        
    def __lt__(self,q):
        if self.degree < q.degree:
            return True
        elif self.degree > q.degree:
            return False
        else:
            return self.node < q.node
    def __le__(self,q):
        return self < q or self == q
    def __ge__(self,q):
        return not self < q
    def __gt__(self,q):
        return not self <= q
    
    def String(self):
        s = ""

        if self.degree == 1:
            s += "(1,"
            s += self.node.String()
        else: 
            s += "(2,"
            s += self.node.String()
        s += ")"
        return s
        
    
    def Output(self):
        print (self.String())
        
class Level_leq_2_Tree (object):
    
    def __init__(self, tree_1 = None, tree_2 = None ):
        if tree_1 is None:
            tree_1 = LevelOneTree()
            tree_2 = LevelTwoTree()
        self.tree_1 = deepcopy(tree_1)
        self.tree_2 = deepcopy(tree_2)
    
    def Level_1_Component (self):
        return self.tree_1
    
    def Level_2_Component (self):
        return self.tree_2
    
    def EnumerateDomain (self):
        for q in self.tree_1.Enumerate():
            yield Level_leq_2_Node(1,q)
        for q in self.tree_2.EnumerateDomain():
            yield Level_leq_2_Node(2,q)
        
    def Cardinality(self):
        return self.tree_1.Cardinality() + self.tree_2.Cardinality()
    
    def ContainsInDomain(self,q):        #does the tree contain q in its domain?
        if q.Degree() == 1:
            return self.tree_1.ContainsElement(q.Node())
        if q.Degree() == 2:
            return self.tree_2.ContainsInDomain(q.Node())
    
    def Value(self,q):                       #when q is of degree 2 and in its domain, output its value. otherwise None.
        if q.Degree()==2 and self.ContainsElementInDomain(q):
            return self.tree_2.Value(q.Node())
            
    def ContainsInDomainStar(self,q):    # does the tree contain q in its domain*?
        if self.ContainsElementInDomain(q):
            return True
        if q.Degree() == 2 :
            if self.tree_2.ContainsInDomainStar(q.Node()):
                return True
        return False
    
    def GetPartialLevelOneTower(self,q):    #outputs the 2Q[q] , the partial level <=1 tower
        if q.Degree() == 2:
            return self.tree_2.GetPartialLevelOneTower(q.Node())
    
    def __eq__(self, Q):
        return self.tree_1 == Q.tree_1 and self.tree_2 == Q.tree_2
    def __ne__(self, Q):
        return not self == Q
        
    def Input(self,d):
        printempty(d)
        print("Input the level <=2 tree:")
        printempty(d)
        print("The level-1 component:")
        self.tree_1.Input(d+indent)
        printempty(d)
        print("The level-2 component:")
        self.tree_2.Input(d+indent)
        printempty(d)
        print("Level <=2 tree input complete!")
        
    
class LevelTwoDescription (FuncNode):
    
    def __init__(self,  node_entry = None, partial_tower = None):
        if node_entry is None:
            node_entry = []
            partial_tower = PartialLevelOneTower()
        super(LevelTwoDescription, self).__init__(node_entry, partial_tower)
        self.immediate_extensions = LevelOneTree()
        #by default, it generates the constant level-2 description:
        #(empty, empty, (0))

        
    def IsConstant(self):               # is it the constant level-2 desc?
        return self.IsEmpty()
        
    def AppendMinusOne(self):           # if discontinous type, append by -1 and complete the partial tower. The result is continuous type
        self.entry.append(-1)
        self.value.AppendCompletion()
        return self
        
    def LengthOfNode(self):
        return self.Length()
    def Node(self):                     # the node in the level-2 tree
        return TreeNode(self.entry)
        
    def PartialTower(self):             #the partial tower component
        return self.value
    def Tree(self):                     # the last tree in the partial tower component
        return self.value.Tree()
    def TreeEntry(self,i):              
        return self.value.TreeEntry(i)

    def NodeSequence(self):             # the node sequence in the partial tower component
        return self.value.NodeSequence()
    def TreeSequence(self):             # the tree sequence in the partial tower component
        return self.value.TreeSequence()
        
    def LevelTwoNodeEntry(self,i):                 # the i-th entry of q
        return self.Entry(i)
    def LevelOneNodeComponent(self,i):                 # p_i
        return self.value.NodeEntry(i)
        
    def Represent(self):            #<q>, to compare the BK orders
        
        r = TreeNode()
        k = self.LengthOfNode()
        P = self.Tree()
        
        if self.IsContinuousType():
            for i in range (k-1):
                r . Append (  P.Rank( self.value.NodeEntry(i) ) )
                r . Append ( self.Entry(i))
            r.Append(-1)
        else:
            for i in range (k):
                r . Append (  P.Rank( self.value.NodeEntry(i) ) )
                r . Append ( self.Entry(i))
            r.Append(-1)
        return r
    
    def __lt__(self,D):
        return self.Represent() < D.Represent()
    def __le__(self,D):
        return self.Represent() <= D.Represent()
    def __gt__(self,D):
        return self.Represent() > D.Represent()
    def __ge__(self,D):
        return self.Represent() >= D.Represent()
    def Equivalent(self,D):          # self ~ D, that is, either self=D or (empty, empty, (0)), ( (-1), {(0)}, ((0)))
        return self.Represent() == self.Represent()
    def NotEquivalent(self,D):          # self !~ D, 
        return self.Represent() != self.Represent()

    def IsLevelTwoDescription(self, Q):         # is it a Q-desc?
        if not Q.ContainsInDomainStar(self.Node()):
            return False
        if self != Q.GetPartialLevelOneTower(self.Node()):
            return False
        return True
        
    def RestrictedTo(self,l):
        return LevelTwoDescription(self.entry[:l], self.value.RestrictedTo(l))
    
    def Minus(self):
        return self.RestrictedTo(self.Length() - 1)
    
class Level_leq_2_Description (object):
    'level <=2 description'
    
    def __init__ (self, degree = None, desc = None ):
        if degree is None:
            degree = 2,
            desc = LevelTwoDescription() 
        #by default, it generates (2, the constant level-2 desc)
        self.degree = deepcopy(degree)
        self.desc = deepcopy(desc)
    
    def Length(self):
        if self.degree == 1:
            return 0
        else:
            return self.desc.Length()

    def LevelOneNodeComponent(self,i):             # p_i
        if self.degree == 2:
            return self.desc.LevelOneNodeComponent(i)
    
    def Tree(self):                 # the tree component of the level-2 desc part
        return self.desc.Tree()
    def TreeEntry(self,i):
        return self.desc.TreeEntry(i)
    def Node(self):                 # the node component of the level <=2 desc part
        if self.degree == 1:
            return self.desc
        else:
            return self.desc.Node()
    def NodeSequence(self):         # the node sequence of the partial tree component of the level-2 desc part
        return self.desc.NodeSequence()
    def TreeSequence(self):         # the node sequence of the partial tree component of the level-2 desc part
        return self.desc.TreeSequence()
        
    def IsContinuousType(self):
        if self.degree == 2:
            if self.desc.IsContinuousType():
                return True
        return False

    def IsDiscontinuousType(self):
        return not self.IsContinuousType()

    
    def IsConstant(self):
        if self.degree == 2:
            if self.desc.IsConstant():
                return True
        return False
        
    def __eq__(self, D):
        return self.degree == D.degree and self.desc == D.desc
    def __ne__(self, D):
        return not self == D
    def __lt__(self,D):
        if self.degree < D.degree:
            return True
        if self.degree > D.degree:
            return False
        return self.desc < D.desc 
    def __le__(self,D):
        return self < D or self == D
    def __ge__(self,D):
        return not self < D
    def __gt__(self,D):
        return not self <= D
    
    
    
    
    
def OplusTwo(q, sigma):         #q oplus sigma, where q is in a level-2 tree
    t = TreeNode()
    k = q.LengthOfNode()
    for i in range(k):
        t.Append(sigma.Value(q.LevelOneNodeComponent(i)))
        t.Append(q.LevelTwoNodeEntry(i))
    return t
    

class Level_21_Description (object):
    'level-(2,1)-description'
    #
    # (d,q,sigma), where d in {1,2}, q is a Q-desc, sigma factors (P,W)
    #               if d=1, sigma is None
    #
    
    def __init__(self, degree = None, desc = None, factor = None):
        if degree is None:
            degree = 2
            desc = LevelTwoDescription()
            factor = LevelOneFactor()
        self.degree = deepcopy(degree)
        self.desc = deepcopy(desc)
        self.factor = deepcopy(factor)
    #the default one is constant
    
    def Node(self):
        if self.degree == 1:
            return self.desc
        else:
            return self.desc.Node()
    
    def String(self,d):

        s = stringempty(d)
        s += "degree: "
        s += str(self.degree)
        s += "\n"
        s += stringempty(d)
        s += "node: "
        if self.degree == 1:
            s += self.desc.String()
        else:
            s += self.desc.Node().String()
        s += "\n"
        if self.degree ==2:
            s += stringempty(d)
            s += "factor map:\n"
            for p in self.desc.Tree().Enumerate():
                s += stringempty(d+indent)
                s += p.String()
                s += "|-->"
                s += self.factor.Value(p).String()
                s += "\n"
        return s
        
    def Output(self,d):
        print(self.String())

    def OutputProperties(self,d):
        printempty(d)
        print("signature:"),
        s = self.Sign()
        for w in s:
            w.Output()
        print(" ")
        
        printempty(d)
        if self.IsContinuousType():
            print("level-1 continuous type")
        else:
            print("level-1 discontinuous type")
        
        printempty(d)
        print("level-1 uniform cofinality:"),
        if self.UCF() == MinusOne():
            print ("-1")
        else:
            self.UCF().Output()
            print (" ")
            
        printempty(d)
        print("level-2 signature:"),
        for q in self.Sign_Star():
            q.Output()
            
    def IsLevel_21_Desc (self):       # is it a level-(2,1)-desc
        if self.degree == 2:
            return self.factor.IsFactor()
        else:
            return True
            
    def IsLevel_21_Desc_2(self, Q):     # is it a Q-desc? 
        
        if self.degree == 2:
            if not self.factor.IsFactor():
                return False
            return self.desc.IsLevelTwoDescription(Q.Level_2_Component())
        
        if self.factor is not None:
            return False
            
        return Q.Level_1_Component().ContainsElement(self.desc)
        
    def IsLevel_21_Desc_21(self, Q,W):  # is it a (Q,W)-desc?
        if not self.IsLevel_21_Desc_2(Q):
            return False
        if self.degree == 1:
            return True
        return self.factor.IsFactorInto(W)
        
    def Degree(self):           # its degree
        return self.degree
    
    def Sign (self):          # its signature
        if self.degree == 1:
            return []
        t = []
        k = self.desc.LengthOfNode()
        for i in range(k):
            t.append(self.factor.Value(self.LevelOneNodeComponent(i)))
        return t
    
    def IsContinuousType(self):    # is it continuous type?
        if self.degree == 2:
            if self.desc.IsContinuousType():
                return True
        return False
    
    def IsDiscontinuousType (self):   # is it discontinuous type?
        return not self.IsContinuousType()
        
    def UCF (self):       #ucf(D)
        if self.degree == 1:
            return MinusOne()
        if self.desc.PartialTower().UniformCofinality() == MinusOne():
            return MinusOne()
        test_ucf = self.desc.PartialTower().UniformCofinality() 
        test_return = self.factor.Value (test_ucf)
        return self.factor.Value( self.desc.PartialTower().UniformCofinality() )
        
    def Sign_Star (self):      # its *-signature

        s = []
        q = self.desc
        k = q.Length()
        
        if self.degree == 1:
            s.append( Level_leq_2_Node ( 1 , q.Node()))
            return s
        
        if q.IsContinuousType():
            for i in range(1, k):
                s.append(  Level_leq_2_Node(2, q.Node().RestrictedTo(i) ))
        else:
            for i in range(1, k+1):
                s.append(  Level_leq_2_Node(2, q.Node().RestrictedTo(i) ))
        return s
    
    def IsContinuousType_Star (self,W):  # is it level-2 W continuous type?
        if self.degree == 1:
            return False
        if self.desc.PartialTower().UniformCofinality() == MinusOne():
            return True
        if self.UCF() == W.SmallestNode():
            return True
        if self.factor.ContainsInRange( W.NodeOnLeft(  self.UCF() ) ):
            return True
        return False

    def IsDiscontinuousType_Star (self,W): 
        return not self.IsContinuousType_Star(W)
        
    def UCF_Star (self,W):         #the level-2 W-uniform cofinality
        
        d = self.degree
        q = self.desc 
        
        if d == 1:
            return Level_leq_2_Node ( 1 , q)
        if q.IsContinuousType():
            if self.IsContinuousType_Star (W):
                #they are extended Q-desc
                return Level_leq_2_Description(2, LevelTwoDescription ( q.entry[:-1], Decapped(q.PartialTower())))  
            else:
                return Level_leq_2_Description(2, LevelTwoDescription ( q.entry[:-1], q.PartialTower()))
        else:
            if self.IsContinuousType_Star (W):
                return Level_leq_2_Description(2, q)
            else:
                return Level_leq_2_Description(2, LevelTwoDescription ( q.entry, Completed(q.PartialTower())))
                
    def IsConstant(self):          #is it the constant level-21-desc?
        if self.degree == 2:
             if self.desc.IsConstant():
                return True
        return False
    
    def __eq__(self, D):    
        if self.degree != D.degree:
            return False
        if self.desc != D.desc:
            return False
        if self.degree == 2:
            return self.factor == D.factor
        return True
        
    def __ne__(self, D):
        return not self == D
    
    def __lt__(self,D):
        if self.degree < D.degree:
            return True
        if self.degree > D.degree:
            return False
        if self.degree == 1:
            return self.desc < D.desc
        return OplusTwo( self.desc , self.factor ) < OplusTwo(D.desc,  D.factor) 
    def __le__(self,D):
        return self < D or self == D
    def __ge__(self,D):
        return not self < D
    def __gt__(self,D):
        return not self <= D    

    def LevelOneNodeComponent(self,k):                 #p_k in the level-2 desc component
        if self.degree == 2:
            return self.desc.LevelOneNodeComponent(k)
    
    def LengthFormal(self):
        if self.degree == 1:
            return 0
        else:
            return self.desc.Length()
            
    def RestrictedToFormal(self,i):
        if self.degree == 1:
            return self
        return Level_21_Description(2, self.desc.RestrictedTo(i), self.factor.RestrictedTo(self.desc.TreeEntry(i)))
        
    def IsProperInitialSegment (self,D):
        if self.LengthFormal() < D.LengthFormal():
            if self == D.RestrictedTo(self.LengthFormal()):
                return True
        return False
        
    def MinusFormal(self):
        return self.RestrictedToFormal (self.LengthFormal()-1)
        
    def IsProperInitialSegmentWithTrees (self,D,Q,W):
    # is self a proper initial segment of D, both are (Q,W)-desc?
        return self.IsProperInitialSegment(D) and D.IsLevel_21_Desc_21(Q,W)

def NextNonConstLevel_21_Desc (D, Q, W):
    
    #
    # input:    D,      a nonconstant(Q,W)-desc or None
    #           Q,      level <=2 tree
    #           W,      level-1 tree
    #
    # output:   the smallest (Q,W)-desc nonconstant, if D is None
    #           the next (Q,W)-desc after D, if nonconstant
    #           None, if the next (Q,W)-desc is constant
    #      


    def NextLevelSmallest(D, Q, W):     
        # the smallest 1-step extension of D , if possible
        # None, otherwise
        if D.IsContinuousType():
            return None
        qq = D.desc 
        q = qq.Node()
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        p_last = pp[-1]
        if p_last.IsContinuousType():
            return None
            
        if p_last.Length() > 1:
            p_last_minus = P.MyNode(p_last.Minus())
            w_last_minus = W.MyNode(sigma.Value(p_last_minus))

        else:
            p_last_minus = P.root
            w_last_minus = W.root
            
        if p_last_minus.BKleft is None:
            #the hanging node is BK leftmost already
            if W.IsNonTrivial():
                w_last = W.SmallestNode()
            else: 
                w_last = W.root
            # assign it to the minimum of W
        else:
            #the hanging node is not BK leftmost
            w_last = sigma.Value(p_last_minus.BKleft).BKright
            # assign it to the BK successor of the sigma value of the predecessor
        if w_last == w_last_minus:
            return None
            # if conflicting with the existing minimum, 
            # impossible to extend
            
        #otherwise, extend it by w_last and -1  
        qq_extend = deepcopy(qq)  
        qq_extend.AppendMinusOne()
        sigma_extend = deepcopy(sigma)
        sigma_extend.AddNodeBelowWithValueNextLevel(p_last_minus, w_last)
        D_extend = Level_21_Description ( 2, qq_extend, sigma_extend )
        # create the new description "D_extend"
        return D_extend    
        
    def SameLevelSmallest(D, Q, W):
        # the smallest description at the same level of D, if possible
        # None otherwise
        
        Q2 = Q.Level_2_Component()
        
        qq = D.desc 
        q = qq.Node()
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        
        if len(pp) == 0:
            return None
        
        if D.IsContinuousType():
            # if D continuous type, 
            p_last = pp[-1]
            
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())
                w_last_minus = W.MyNode(sigma.Value(p_last_minus))

            else:
                p_last_minus = P.root
                w_last_minus = W.root

            if not Q2.MyNode(q.Minus()).IsTerminal():
                # there is a node in Q at the same level, then it is the smallest
                q_next = Q2.MyNode(q.Minus()).first_child
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_21_Description (2, qq_next, sigma)
                return D_next
            else:
                # no node at the same level
                # then we must alter the last entry in W
                w_last = W.MyNode(sigma.Value(p_last))
                w_next = w_last.BKright
                if w_next == w_last_minus:
                    # the next entry in W is already in use
                    # impossible to move
                    return None
                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                D_next = Level_21_Description ( 2, qq, sigma_next )
                return D_next
            
        else:
            # if D discontinuous type
            if len(pp) == 1:
                # this happens iff D is constant
                return None
            else:
                p_last = pp[-2]
                w_last = W.MyNode(sigma.Value(p_last))
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())
                w_last_minus = W.MyNode(sigma.Value(p_last_minus))
            else:
                p_last_minus = P.root
                w_last_minus = W.root
            # if D discontinuous type, 
            if not Q2.MyNode(q).IsLastBitRightMost():
                # firstly search the next node at the same level in Q
                q_next = Q2.MyNode(q).right
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_21_Description (2, qq_next, sigma)
                return D_next
            else:
                # the current node is already rightmost at this level. 
                # search for the next node in W, and the q-entry must end with -1
                w_next = w_last.BKright
                if w_next == w_last_minus:
                    # the next entry in W is already in use
                    # impossible to move
                    return None
                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                qq_next = deepcopy(qq.Minus())
                qq_next.AppendMinusOne()
                D_next = Level_21_Description ( 2, qq_next, sigma_next )
                return D_next               
    
    
    Q1 = Q.Level_1_Component() 
    Q2 = Q.Level_2_Component()
    
    if D is None:
        if Q1.IsTrivial():
            if W.IsNonTrivial():
                return NextLevelSmallest(Level_21_Description(), Q, W)
                # if W is nontrivial, the next is (w,-1), where w is the smallest in W
            else:
                return None
                # if W is trivial, the next is the constant desc
                # so return None
        #now assume that q_next is nonempty
        return Level_21_Description( 1, Q1.SmallestNode(), None)
            

    
    if D.Degree() == 1:
    # D is degree 1, i.e. a node in Q1
        q = D.desc
        q_next = Q1.MyNode(q).BKright
        if q_next.IsEmpty():
            if W.IsNonTrivial():
                return NextLevelSmallest(Level_21_Description(), Q, W)
                # if W is nontrivial, the next is (w,-1), where w is the smallest in W
            else:
                return None
                # if W is trivial, the next is the constant desc
                # so return None
        #now assume that q_next is nonempty
        return Level_21_Description( 1, q_next, None)
            
            
    #now assume that D is of degree 2
    
    
    bound = SameLevelSmallest(D, Q, W)
    # try to move the last bit right
    
    if bound is None:
        #if this level is rightmost already
        #move back up one level
        if D.MinusFormal().IsConstant():
            return None
            # if back to the constant, return None
        else:
            return D.MinusFormal()
            # otherwise, return the 1-level shortening
    else:
        # otherwise, move along bound on the leftmost path
        while bound is not None:            
            current = bound 
            bound = NextLevelSmallest(current, Q, W)
        return current    

def EnumerateNonConstLevel_21_Desc (Q,W):
    D = None
    while True:
        D = NextNonConstLevel_21_Desc (D, Q, W)
        if D is not None:
            yield D
        else:
            return

def TensorProduct_21 ( Q, W):
    # returns psi factoring (S,Q,W), S is a representation of Q \otimes W
    psi = Level_121_Factor()
    D = None
    for D in EnumerateNonConstLevel_21_Desc(Q,W):
        psi.AddNodeBelowWithValueNextLevel( psi.root, D)
    return psi
    
def IsLevelOneNoGapExtension (w,W,w_prime):  # is w triangle_1^W w'?
    if W.ContainsElement(w) and w_prime < w and (not W.ContainsElement(w_prime)):
        if w == W.SmallestNode():
            return True
        if w.BKleft < w_prime:
            return True
    return False

def IsLevel_21_NoGapExtension_1 (D, Q, W, D_prime): # is D triangle_1^{Q,W} D'?
    if D.IsLevel_21_Desc_21(Q,W) and D_prime < D and D_prime.IsLevel_21_Desc_2(Q) and (not D_prime.IsLevel_21_Desc_21(Q,W)):
        e = MakeLevel_21_Desc(Q,W)
        i = 0
        if e[0] == D:
            return True
        while True:
            if e[i+1] == D:
                if e[i] < D_prime:
                    return True
            i += 1
    return False


def IsLevel_21_NoGapExtension_2 (D, Q,  D_prime): # is D triangle_2^{Q} D'?
    if D.IsLevel_21_Desc_2(Q) and D_prime < D and (not D_prime.IsLevel_21_Desc_2(Q)):
        e = MakeLevel_21_Desc(Q,W)
        i = 0
        if e[0] == D:
            return True
        while True:
            if e[i+1] == D:
                if e[i] < D_prime:
                    return True
            i += 1
    return False


class Level_121_Factor(LevelOneFactor):
    'level-(1,2,1) factoring map'
    
    def __init__(self):
        super(Level_121_Factor,self).__init__()
        self.root.value = Level_21_Description()
        #the constant Q,W-desc is assigned the root

    def IsLevel_121_Factor (self):
        return self.IsFactor()
        

    def IsLevel_121_FactorInto_2 (self, Q):     # does it factor (*, Q, W)?
        
        if self.IsTrivial():
            return True
        if not self.IsFactor():
            return False
        current = self.root.BKleft
        while current is not None:
            if not self.Value(current).IsLevel_21_Desc_2(Q):
                return False
            current = current.BKleft
        return True
        
    def IsLevel_121_FactorInto_21(self, Q, W):  #does it factor into (*, Q, W)?
        if self.IsTrivial():
            return True
        if not self.IsFactor():
            return False
        current = self.root.BKleft
        while current is not None:
            if not self.Value(current).IsLevel_21_Desc_21(Q,W):
                return False
            current = current.BKleft
        return True

def LevelOneTreeOfCardinalityOne():
    P = LevelOneTree()
    P.AddNodeBelowNextLevel(P.root)
    return P


def Identity_121_Origin ( S ):      # id_{*,S}, which factors (S,Q^0,S)
    out = Level_121_Factor()
    out.CopyIntoDomain(S)
    for e in out.EnumerateDomain():
        factor = LevelOneFactor()
        factor.CopyIntoDomain(LevelOneTreeOfCardinalityOne())
        factor.MakeValue( factor.root.first_child, e)
        desc = Level_21_Description( 2, LevelTwoDescription(), factor)
        out.MakeValue( desc )
    return out
    
    
def MakePartialLevelOneTowerFromNodes ( s ):    
    # 
    #   input:  s, a sequence of nodes
    #
    #   output: a partial level-1 tower of cont type whose node sequence is s, if possible
    #           None, otherwise
    #
    if len(s) == 0:
        return None
    out = PartialLevelOneTower()
    out.AppendCompletion()
    if len(s) == 1:
        if s[0] == Node([0]):
            return out
        else:
            return None
    for i in range(1, len(s)):
        if PartialLevelOneTree(out, s[i]).IsPartialLevelOneTree():
            out.AppendNode(s[i])
            out.AppendCompletion()
        else:
            return None
    return out 
    
def Contraction (A):        #the contaction of the double sequence A
    t = []
    for a in A:
        t = t + a
    output = []
    for b in t:
        if b not in output:
            output.append(b)
    return output
    
class Level_221_Description (Level_21_Description):
    'level-(2,2,1)-description'
    # A level-221-Desc is also a level-21-Desc,only the target of the factor is different
    
    def __init__(self, degree = None, desc = None, factor = None):
        if degree is None:
            degree = 2
            desc = LevelTwoDescription()
            factor = Level_121_Factor()
        super(Level_221_Description, self).__init__(degree, desc, factor)
        #by default, the value of empty is the trivial level-121-factor
    

            
    def RestrictedToFormal(self,i):
        if self.degree == 1:
            return self
        return Level_221_Description(2, self.desc.RestrictedTo(i), self.factor.RestrictedTo(self.desc.TreeEntry(i)))
        


    def String(self,d):
        s = stringempty(d)
        s += "degree:"
        s += str(self.degree)
        s += "\n"
        s += stringempty(d)
        s += "node:"
        if self.degree == 1:
            s += self.desc.String()
        else:
            s += self.desc.Node().String()
        s += "\n"
        if self.degree ==2:
            s += stringempty(d)
            s += "factor map:\n"
            for p in self.desc.Tree().Enumerate():
                s += stringempty(d+indent)
                s += p.String()
                s += "|-->"
                s += "the follofing level-(2,1) description:\n"
                s += self.factor.Value(p).String(d+indent+indent)
                s += "\n"
        return s
    
    
    def Output(self,d):
        print(self.String(d))
    
    def BaseUCF (self):
        s_ucf = self.desc.PartialTower().UniformCofinality()
        if s_ucf == MinusOne():
            return MinusOne()
        return self.factor.Value(s_ucf).UCF()
    
    def BaseTower (self):
        #
        # if self is a (T,Q,'vec{W})-desc, outputs \vec{W}
        # if self is a (T,Q,-1)-desc, outputs MinusOne()
        #
        # if self is not a (2,2,1)-desc, outputs None
        #
        if self.degree == 1:
            if self.IsLevel_21_Desc():
                return MinusOne()
            return None
        # degree 1
        
        # assume degree == 2
        tau = self.factor
        tt = self.desc 
        t= tt.Node()
        SS = tt.PartialTower()
        S = SS.Tree()
        ss = SS.NodeSequence()
        k = t.Length()
        
        if not tau.IsLevel_121_Factor():
            return None
            
        if tt.IsConstant():
            if tau.IsTrivial():
                return PartialLevelOneTower()
            return None
        #constant 221 desc
        
        #nonconstant 221 desc
        sign = []
        for i in range(k):
            sign.append(  tau.Value(ss[i]).Sign() )
        WW_cont = MakePartialLevelOneTowerFromNodes ( Contraction (sign) )
        if WW_cont is None:
            return None
        #make a tower of cont type
        
        W = WW_cont.Tree()
        # the last tree of the tower. now need to decide the hanging node
        
        w_cont = WW_cont.LastNodeWhenContinuous()
            
        if t.IsContinuousType() and (w_cont not in Contraction(sign[:-1])):
            if tau.Value(ss[k-1]).IsContinuousType():
                return None
            
        if SS.UniformCofinality() == MinusOne():
            WW_cont.AppendNode(MinusOne())
            return WW_cont      # now it is discontinuous, having appendid -1
        
        test_SS_unif_cof = SS.UniformCofinality()
        test_tau_value = tau.Value(test_SS_unif_cof)
        test_w_unif_cof = test_tau_value.UCF()
        
        w_unif_cof = tau.Value(SS.UniformCofinality()).UCF()
        if w_unif_cof == MinusOne():
            WW_cont.AppendNode(MinusOne())
            return WW_cont      # now it is discontinuous, having appendid -1
        w_new = Node ( w_unif_cof.entry + [W.MyNode(w_unif_cof).number_of_children] )
        WW_cont.AppendNode(w_new)
        return WW_cont      # now it is discontinuous, having appended w_new
    
    def BaseTree (self):
        return self.BaseTower().Tree()
            
    def IsLevel_221_Desc (self):    # is it a 221 desc?
        return self.BaseTower() is not None    
    
    def IsLevel_221_Desc_2 (self,T): # is it a (T,*,*)-desc?
        WW = self.BaseTower()

        if WW is None:
            return False
            
        if WW == MinusOne():
            return self.IsLevel_21_Desc_2 (T)
            
        return self.desc.IsLevelTwoDescription(T)
        
    
    def IsLevel_221_Desc_22(self, T, Q ):
        # is it a (T,Q,*)-desc?
        
        WW = self.BaseTower()

        if WW is None:
            return False
            
        if WW == MinusOne():
            return self.IsLevel_21_Desc_2 (T)
        
        tt = self.desc
        tau = self.factor
        return tt.IsLevelTwoDescription(T) and tau.IsLevel_121_FactorInto_2 (Q)
        
    
    def IsLevel_221_Desc_221(self, T, Q, WW):   
        #is it a (T,Q,\vec{W})-desc?    
        
        base = self.BaseTower()
        return self.IsLevel_221_Desc_22(T,Q) and base == WW
     
    def IsLevel_221_Desc_221_TreeOnly (self, T, Q, W):
        # is it a (T,Q,WW)-desc where W is the last tree of WW?
        base = self.BaseTower()
        return self.IsLevel_221_Desc_22 (T,Q) and W == base.Tree()
    
    def Sign(self):
        if self.degree == 1:
            return []
        t = []
        k = self.desc.LengthOfNode()
        for i in range(k):
            t.append(self.factor.Value(self.LevelOneNodeComponent(i)).Sign_Star())
        return Contraction(t)

    def IsContinuousType (self):
        if self.degree == 2:
            if self.desc.IsContinuousType():
                k = self.desc.Length()
                tau = self.factor
                W = self.BaseTree()
                if tau.Value(self.desc.NodeSequence(k-1)).IsContinuousType_Star(W):
                    return True
        return False
    
    def IsDiscontinuousType(self):
        return not self.IsContinuousType()
    
    def UCF(self):
        d = self.degree
        if d == 1:
            return Level_leq_2_Node ( 0, MinusOne())
        
        tt = self.desc 
        k = tt.Length()
        SS = tt.PartialTower()
        s_star = SS.UniformCofinality()
        tau = self.factor
        W = self.BaseTree()
        
        if s_star == MinusOne():
            return  Level_leq_2_Node ( 0, MinusOne())
        return tau.Value(s_star).UCF_Star(W)

    def IsDiscontinuousType_Plus(self):
        WW = self.BaseTower()
        if WW.IsDiscontinuousType():
            return True
        return False
    
    def UCF_plus(self):
        W_plus = self.BaseTower().Completion()
        return self.factor.Value(self.desc.PartialTower().UniformCofinality()).UCF_Star(W_plus)
    
    # star-Q-signature already define!
    
    def IsContinuousType_Star (self, Q):
        if self.degree == 1:
            return False
        s_star = self.desc.PartialTower().UniformCofinality()
        if s_star == MinusOne():
            return True
        
        value_star = self.factor.Value(s_star)
        
        W = self.BaseTree()
        DD = MakeLevel_21_Desc(Q,W)
        
        for i in range(len(DD)):
            if value_star == DD[i]:
                break
            
        if i == 0:
            return True
        
        if self.factor.ContainsInRange( DD[i-1] ):
            return True
            
        return False

    def Length(self):
        WW = self.BaseTower()
        if isinstance(WW , Node):
            return 0
        return WW.LengthOfNodeSequence()-1
        
    def RestrictedTo(self, m_bar):
        WW = self.BaseTower()
        W_bar = WW.TreeEntry(m_bar)
        
        ss = self.desc.NodeSequence()
        SS = self.desc.TreeSequence()
        
        tau = self.factor
        for l in range(len(ss)):
            if not tau.Value(ss[l]).IsLevel_21_Desc_21( Q, W_bar ):
                break
        s = ss[l]
        tt = self.desc
        
        DD = MakeLevel_21_Desc(Q,W_bar)
        for D in DD:
            if D > tau.Value(s):
                break
        if D != tau.Value(s.Minus()):
            new_tt = tt.RestrictedTo(l)
            new_tt.AppendMinusOne()
            new_tau = tau.RestrictedTo ( SS[l+1] )
            new_tau.MakeValue( s , D )
        else:
            new_tt = tt.RestrictedTo(l)
            new_tau = tau.RestrictedTo ( SS[l] )
        return Level_221_Description (2, new_tt, new_tau)
    
    def Minus(self):
        return self.RestrictedTo(self.Length()-1)
    
    def IsProperInitialSegment(self, C):
        if self.Length() < C.Length():
            if self == C.RestrictedTo(self.Length()):
                return True
        return False
 

def Level_21_1_Extension (D, Ww):
    #
    # given D, a (*,W)-desc, whose ucf is w^-, where Ww = (W,w) is a partial tree
    # outputs D', the least such that D is 1-initial segment of D'
    #
    
    W = Ww.tree
    w = Ww.node

    qq = D.desc 
    sigma = D.factor
    pp = qq.NodeSequence()
    p = pp[-1]
    
    if D.IsDiscontinuousType():
        sigma_extension = deepcopy(sigma)
        sigma_extension.AddNodeBelowWithValueNextLevel(p.Minus(), w)
        qq_extension = deepcopy(qq)
        qq_extension.AppendMinusOne()
        D_extension = Level_21_Description ( 2, qq_extension, sigma_extension)
    else:
        sigma_extension = deepcopy(sigma)
        sigma_extension.MakeValue(p, w)
        D_extension = Level_21_Description ( 2, qq, sigma_extension)
        
    return D_extension
        
def Level_21_1_Next (D_plus, D, Q, Ww):
    # 
    # given D, a (Q,W)-desc, whose ucf is w^-, where Ww = (W,w) is a partial tree
    # given D_plus, a 1-extension of D,
    # outputs D', the next 1-extension of D
    #
    
    W = Ww.tree
    w = Ww.node
    
    qq = D.desc 
    q = qq.Node()
    sigma = D.factor
    pp = qq.NodeSequence()
    p = pp[-1]
    qq_plus = D_plus.desc
    q_plus = qq_plus.Node()
    W_plus = Ww.Completion()


    D_next = NextNonConstLevel_21_Desc(D_plus, Q, W_plus)
    if D_next is None:
        return None
    qq_next = D_next.desc 
    q_next = qq_next.Node()
    sigma_next = D_next.factor
    sigma_plus = D_plus.factor
    
    Q2 = Q.Level_2_Component()
    
    if q.IsDiscontinuousType():
        if not q.IsProperInitialSegment (q_next):
            return None
        if sigma_next.Value(Q2.Value(q).Node()) != w:
            return None
        return D_next
        
    else:
        if not q.Minus().IsProperInitialSegment (q_next):
            return None
        if sigma_next.Value(Q2.Value(q.Minus()).Node()) != w:
            return None
        return D_next

    

def Level_221_PreExtension ( C, T, Q, WW):
    #
    # given C, a (T,Q,WW)-desc
    # output the smallest C', a (T,Q \otimes W')-desc that extends C as a (T,Q \otimes W)-desc
    #       None if not exist
    #
    if isinstance(WW,Node):
        return None
        # if WW=(-1), C cannot be extended
    
    tt = C.desc
    tau = C.factor
    t = tt.Node()
    S = tt.Tree()
    ss = tt.NodeSequence()
    s = ss[-1]
    W = WW.Tree()
    ww = WW.NodeSequence()
    w = ww[-1]
    Ww = WW.LastPartialTreeWhenDiscontinuous()
    
    if s.IsMinusOne():
        return None
        # if WW has ends with (-1), WW has no completion
    
    
    if t.IsDiscontinuousType():
        s_minus = s.Minus()
        D = tau.Value(s_minus)
        D_extension = Level_21_1_Extension (D, Ww)
        tau_extension = deepcopy(tau)
        tau_extension.AddNodeBelowWithValueNextLevel(s.Minus(), D_extension)
        tt_extension = deepcopy(tt)
        tt_extension.AppendMinusOne()
        C_extension = Level_221_Description ( 2, tt_extension, tau_extension)
    else:
        D = tau.Value(s)
        D_extension = Level_21_1_Extension (D, Ww)
        tau_extension = deepcopy(tau)
        tau_extension.MakeValue(s, D_extension)
        C_extension = Level_221_Description ( 2, tt, tau_extension)
        
    return C_extension
        
        
def Level_221_Next (C_plus, C, T, Q, WW):
    #
    # given C_plus, a (T,Q W')-desc, or None, C , a (T,Q, WW)-desc
    # outputs C' such that (C')^- = C_plus^-, C' > C_plus and C' is the smallest such
    #       None if doesn't exist
    #

    def NextLevelSmallest(D, Q, W, Zz):     
        # the smallest 1-step extension of D , as a (Q, W \otimes Z')-desc,  if possible
        # given D is (Q,W \otimes Z)-desc
        # None, otherwise
        
        qq = D.desc 
        q = qq.Node()
        
        Z_plus = Zz.Completion()
        z = Zz.Node()
        
        if q.IsContinuousType():
            return None
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        p_last = pp[-1] 
        if p_last.IsContinuousType():
            return None
            
        if p_last.Length() > 1:
            p_last_minus = P.MyNode(p_last.Minus())

        else:
            p_last_minus = P.root
        
        w_last_minus = sigma.Value(p_last_minus)

        if p_last_minus.BKleft is None:
            #the hanging node is BK leftmost already
            w_last = NextNonConstLevel_21_Desc(None, W,Z_plus) 
            
        else:
            #the hanging node is not BK leftmost
            w_last = NextNonConstLevel_21_Desc (sigma.Value(p_last_minus.BKleft),W,Z_plus)
            
        w_next = w_last
        if w_next is None:
            return None
        if w_next == w_last_minus:
            return None
            # if conflicting with the existing minimum, 
            # impossible to extend
            
        #otherwise, extend it by w_last and -1  
        qq_extend = deepcopy(qq)  
        qq_extend.AppendMinusOne()
        sigma_extend = deepcopy(sigma)
        sigma_extend.AddNodeBelowWithValueNextLevel(p_last_minus, w_next)
        D_extend = Level_221_Description ( 2, qq_extend, sigma_extend )
        # create the new description "D_extend"
        return D_extend    
        
    def NextLevelSmallestExtend (D, Q, W, Zz):
     
         # the smallest 1-step extension of D , as a (Q, W \otimes Z')-desc,  if possible
        # given D is (Q,W \otimes Z)-desc
        # None, otherwise
        
        qq = D.desc 
        q = qq.Node()
        
        Z_plus = Zz.Completion()
        z = Zz.Node()
        
        if q.IsContinuousType():
            return None
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        p_last = pp[-1] 
        if p_last.IsContinuousType():
            return None
            
        if p_last.Length() > 1:
            p_last_minus = P.MyNode(p_last.Minus())

        else:
            p_last_minus = P.root
        
        w_last_minus = sigma.Value(p_last_minus)

        if p_last_minus.BKleft is None:
            #the hanging node is BK leftmost already
            w_last = NextNonConstLevel_21_Desc(None, W,Z_plus) 
            
        else:
            #the hanging node is not BK leftmost
            w_last = NextNonConstLevel_21_Desc (sigma.Value(p_last_minus.BKleft),W,Z_plus)
            
        w_next = w_last
        
        
        while w_next is not None:
            if w_next != w_last_minus:
                if z not in w_next.Sign():
                    w_next = NextNonConstLevel_21_Desc(w_next,W,Z_plus)
                else:
                    break
            else:
                break

        if w_next is None:
            return None
                    
        if w_next == w_last_minus:
            return None
            # if conflicting with the existing minimum, 
            # impossible to extend
            
        #otherwise, extend it by w_last and -1  
        qq_extend = deepcopy(qq)  
        qq_extend.AppendMinusOne()
        sigma_extend = deepcopy(sigma)
        sigma_extend.AddNodeBelowWithValueNextLevel(p_last_minus, w_next)
        D_extend = Level_221_Description ( 2, qq_extend, sigma_extend )
        # create the new description "D_extend"
        return D_extend    



 
    def SameLevelSmallest(D, Q, W, Zz):
        # the smallest description at the same level of D, as a (Q, W \otimes Z_plus)-desc, if possible, 
        #   so that they have the same formal predecessor
        # given D is of degree 2, a (Q, W \otimes Z)-desc
        # None otherwise
        
        Q2 = Q.Level_2_Component()
        
        qq = D.desc 
        q = qq.Node()
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        
        Z_plus = Zz.Completion()
        z = Zz.Node()
        
        if len(pp) == 0:
            return None
        
        if q.IsContinuousType():
            # if q continuous type, 
            p_last = pp[-1]
            
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())
                w_last_minus = sigma.Value(p_last_minus)

            else:
                p_last_minus = P.root
                w_last_minus = sigma.Value(p_last_minus)

            if not Q2.MyNode(q.Minus()).IsTerminal():
                # there is a node in Q at the same level, then it is the smallest
                q_next = Q2.MyNode(q.Minus()).first_child
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_221_Description (2, qq_next, sigma)
                return D_next
            else:
                # no node at the same level
                # then we must alter the last entry in W,Z
                w_last = sigma.Value(p_last)
                w_next = NextNonConstLevel_21_Desc(w_last,W,Z_plus)
                if w_next is None:
                    return None
                if w_next == w_last_minus:
                    # the next entry in W,Z is already in use
                    # impossible to move
                    return None
                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                D_next = Level_221_Description ( 2, qq, sigma_next )
                return D_next
            
        else:
            # if qq discontinuous type
            if len(pp) == 1:
                # this happens iff D is constant
                return None
            else:
                p_last = pp[-2]
                w_last = sigma.Value(p_last)
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())
                w_last_minus = sigma.Value(p_last_minus)
            else:
                p_last_minus = P.root
                w_last_minus = sigma.Value(p_last_minus)
                
            if not Q2.MyNode(q).IsLastBitRightMost():
                # firstly search the next node at the same level in Q
                q_next = Q2.MyNode(q).right
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_221_Description (2, qq_next, sigma)
                return D_next
            else:
                # the current node is already rightmost at this level. 
                # search for the next node in W, and the q-entry must end with -1
                
                w_last = sigma.Value(p_last)
                w_next = NextNonConstLevel_21_Desc(w_last,W,Z_plus)
                if w_next is None:
                    return None
                if w_next == w_last_minus:
                    # the next entry in W,Z is already in use
                    # impossible to move
                    return None

                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                qq_next = deepcopy(qq.Minus())
                qq_next.AppendMinusOne()
                D_next = Level_221_Description ( 2, qq_next, sigma_next )
                return D_next               
    
    def SameLevelSmallestExtend (D, D_minus, Q, W, Zz):
        #
        # Given D and D_minus, 
        # where formallength(D) = formallength(D_minus) if the node of D_minus cont type, +1 if discont type
        # 
        # 
        # outputs the next (Q, W \otimes Z_plus)-desc D', so that D_plus and D' have the common formal Minus(): D.Minus()
        #
 
        Q2 = Q.Level_2_Component()
        Z_plus = Zz.Completion()
        z = Zz.Node()
        
        qq = D.desc 
        q = qq.Node()
        PP = qq.PartialTower()
        P = PP.Tree()
        pp = PP.NodeSequence()
        sigma = D.factor
        if q.IsDiscontinuousType():
            w_last = sigma.Value(pp[-2])
        else:
            w_last = sigma.Value(pp[-1])
            
        qq_minus = D_minus.desc 
        q_minus = qq_minus.Node()
        sigma_minus = D_minus.factor
        pp_minus = D_minus.desc.PartialTower().NodeSequence()
        if q_minus.IsDiscontinuousType():
            w_last_minus = sigma_minus.Value(pp_minus[-1].Minus())
        else:
            w_last_minus = sigma_minus.Value(pp_minus[-1])
        
        if q.IsDiscontinuousType():
            if len(pp) == 0:
                return None
            if len(pp) == 1:
                # this happens iff D is constant
                # of course it never happens, given the assumption of the parameters of this function
                return None
            else:
                p_last = pp[-2]
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())
            else:
                p_last_minus = P.root
                
            if not Q2.MyNode(q).IsLastBitRightMost():
                # firstly search the next node at the same level in Q
                q_next = Q2.MyNode(q).right
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_221_Description (2, qq_next, sigma)
                return D_next
            else:
                # the current node is already rightmost at this level. 
                # search for the next node in W, and the q-entry must end with -1
                w_next = Level_21_1_Next(w_last,w_last_minus,W,Zz)
                
                while w_next is not None:
                    if w_next != w_last_minus:
                        if z not in w_next.Sign():
                            w_next = NextNonConstLevel_21_Desc(w_next,W,Z_plus)
                        else:
                            break
                    else:
                        break

                if w_next is None:
                    return None
                    

                if w_next == w_last_minus:
                    # the next entry in W,Z is already in use
                    # impossible to move
                    return None                    
                
                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                qq_next = deepcopy(qq.Minus())
                qq_next.AppendMinusOne()
                D_next = Level_221_Description ( 2, qq_next, sigma_next )
                return D_next 
        else:
            p_last = pp[-1]
            
            if p_last.Length() > 1:
                p_last_minus = P.MyNode(p_last.Minus())

            else:
                p_last_minus = P.root

            if not Q2.MyNode(q.Minus()).IsTerminal():
                # there is a node in Q at the same level, then it is the smallest
                q_next = Q2.MyNode(q.Minus()).first_child
                qq_next = Q2.GetLevelTwoDescription(q_next)
                D_next = Level_221_Description (2, qq_next, sigma)
                return D_next
            else:
                # no node at the same level
                # then we must alter the last entry in W,Z
                w_last = sigma.Value(p_last)
                w_next = Level_21_1_Next(w_last,w_last_minus,W,Zz)
                
                while w_next is not None:
                    if w_next != w_last_minus:
                        if z not in w_next.Sign():
                            w_next = NextNonConstLevel_21_Desc(w_next,W,Z_plus)
                        else:
                            break
                    else:
                        break

                if w_next is None:
                    return None
                if w_next == w_last_minus:
                    # the next entry in W,Z is already in use
                    # impossible to move
                    return None
                sigma_next = deepcopy(sigma)
                sigma_next.MakeValue(p_last, w_next)
                D_next = Level_221_Description ( 2, qq, sigma_next )
                return D_next
        
                    
    Q1 = Q.Level_1_Component()
    Q2 = Q.Level_2_Component()
#    if C_plus.degree == 1:
#        return NextNonConstLevel_21_Desc(C_plus, T, Q1)
#    
    #now assume C_plus has degree 2
#    if C_plus.IsConstant():
#        return None
#    
    #now assume C_plus is non-constant
    #we would like to extend C
    tt = C.desc
    tau = C.factor
    ss = tt.NodeSequence()
    s = ss[-1]
    t = tt.Node()
    
    
    Ww = WW.LastPartialTreeWhenDiscontinuous()
    W = WW.Tree()
    W_plus = WW.Completion()
    w = Ww.Node()
    
    if t.IsDiscontinuousType():
        # if t discontinuous type, all extensions of C must formally extend C
        
        D = tau.Value(s.Minus())
        # D is the level-21 desc to be extended
        
        critical_length = t.Length() + 1
        
    else:
        
        
        D = tau.Value(s)
        # D is the level-21 desc to be extended
        
        critical_length = t.Length()
    
    
    current = C_plus
    
    if current is not None:
        if current.LengthFormal() == critical_length:
            bound = SameLevelSmallestExtend(current, C, T, Q, Ww)
        else: 
            bound = SameLevelSmallest(current, T, Q, Ww)
        # try to move the last bit right
    else:
        bound = Level_221_PreExtension (C, T, Q, WW)
    # bound is a candidate

    if bound is not None:
        while bound is not None:
            current = bound
            bound = NextLevelSmallest(current, T, Q, Ww)
        bound = current
    
    
    while True:
        
        if bound is None:
            if current is None:
                return None
            if current.Node().Length() == critical_length:
                return None
            current = current.MinusFormal()
            bound = current
            continue
        
        else:
            if bound.Node().Length() == critical_length:
                if bound.Node().IsContinuousType():
                    D_last = bound.factor.Value(bound.desc.PartialTower().LastNodeWhenContinuous())
                    if D_last.IsContinuousType():
                        if D_last.UCF() == w:
                            current = SameLevelSmallestExtend(bound, C, T, Q, Ww)
                            bound = current
                            while bound is not None:
                                current = bound
                                bound = NextLevelSmallest(current, T, Q, Ww)
                            bound = current
                            continue

        print("get a description!")
        bound.Output(5)
        return bound

    
    

def EnumerateLevel_221_Extensions (C,T,Q,WW):
    
    C_plus = Level_221_Next(None, C,T,Q,WW)
    while C_plus is not None:
        yield C_plus
        C_plus = Level_221_Next(C_plus, C, T, Q, WW)
    return
    
class Level_leq_2_Factor (object):
    ' a factoring map between level <=2 trees'
    
    def __init__(self, domain = None, factor_1 = None, factor_2 = None):
        if domain is None:
            domain = Level_leq_2_Tree()
            factor_1 = LevelOneFactor()
            factor_2 = FuncTree( Node([]) )
            factor_2.root.immediate_extensions = LevelOneTree()
        self.domain = domain
        self.factor_1 = factor_1
        self.factor_2 = factor_2
        
    
    
class Level_222_Factor (Level_leq_2_Factor):
    'a level-(2,2,2)-factoring map'
    
    def __init__(self, domain = None, factor_1 = None, factor_2 = None):
        if domain is None:
            domain = Level_leq_2_Tree()
            factor_1 = LevelOneFactor()
            factor_2 = FuncTree( Level_221_Description() )
            factor_2.root.immediate_extensions = LevelOneTree()
        self.domain = domain
        self.factor_1 = factor_1
        self.factor_2 = factor_2
        
    def Value(self, qq):    # the value at qq = (d,q)
        if qq.degree == 1:
            return self.factor_1.Value(qq.node)
        return self.factor_2.Value(qq.node)
        
    def IsLevel_222_Factor (self):
        #does it factor (self.domain, *, *) ?
        
        for x in self.domain.EnumerateDomain() :
            if not self.Value(x).IsLevel_221_Desc():
                return False
            if x.degree == 1:
                if not self.Value(x).Length () == 0:
                    return False
            else:
                if not self.Value(x).BaseTower == self.domain.Level_2_Component.GetPartialLevelOneTower(x.node):
                    return False
        
        if not self.Value(Level_leq_2_Node()).IsConstant():
            return False
        
        for [x,x_prime] in combinations(self.domain.EnumerateDomain() ,2):
            if self.Value(x) >= self.Value(x_prime):
                return False 
        
        for x in self.domain.EnumerateDomain() :
            if x.degree == 2 and (not x.IsConstant()):
                if not self.Value(x.Minus()).IsProperInitialSegment(self.Value(x)):
                    return False
                    
        return True
                
    def IsLevel_222_Factor_2(self,T):
        #does it factor (self.domain,T,*)?
        if not self.IsLevel_222_Factor():
            return False
        for x in self.domain.EnumerateDomain():
            if not self.Value(x).IsLevel_221_Desc_2(T):
                return False
        return True
        
    def IsLevel_222_Factor_22(self,T,Q):
        #does it factor (self.domain,T,Q)?
        if not self.IsLevel_222_Factor():
            return False
        for x in self.domain.EnumerateDomain():
            if not self.Value(x).IsLevel_221_Desc_22(T,Q):
                return False
        return True    

def CreatePartialLevelOneTreeFromUCF (W, w):
    
    if w == MinusOne():
        return PartialLevelOneTree(W, MinusOne())
    w_plus = TreeNode( w.entry + [W.MyNode(w).number_of_children])
    return PartialLevelOneTree(W, w_plus)
        
def TensorProduct_22( T,Q):
    # outputs psi that factors (X,T, Q), X is a representation of T \otimes Q
    
    Q1 = Q.Level_1_Component()
    Q2 = Q.Level_2_Component()
    
    psi1 = TensorProduct_21( T, Q1)
    X1 = psi1.Domain()
    
    X2 = LevelTwoTree()
    psi2 = FuncTree(Level_221_Description())
    psi2.root.immediate_extensions = LevelOneTree()
    
    current_node = X2.root 
        
    while True:
        current_desc = psi2.Value(current_node)
        WW = X2.GetPartialLevelOneTower(current_node)
        if WW.UniformCofinality() != MinusOne():
            W_plus = WW.Completion()
            for C in EnumerateLevel_221_Extensions(current_desc, T, Q, WW):
                Ww_plus = CreatePartialLevelOneTreeFromUCF (W_plus, C.BaseUCF() )
                X2.AddNodeBelowWithValueNextLevel (current_node, Ww_plus)
                psi2.AddNodeBelowWithValueNextLevel (current_node, C)
        if current_node.IsTerminal():
            while current_node is not None:
                if current_node.IsLastBitRightMost():
                    current_node = current_node.parent 
                else:
                    current_node = current_node.right
                    break
            if current_node is None:
                break
        else:
            current_node = current_node.first_child
 
    X = Level_leq_2_Tree(X1,X2)
    
    psi = Level_222_Factor(X, psi1, psi2)
    return psi
    
#print("Input Q\n")    
#Q = Level_leq_2_Tree()
#Q.Input(0)




#print("Input W\n")
#W = LevelOneTree()

#W.Input(0)

#print("Computing.....")

#current = NextNonConstLevel_21_Desc(None, Q,W)
#i = 1

#fo = open("level_21.txt", "wb")

#while current is not None:
    #s = "Description " + str(i) + ":\n" + current.String(2) + "\n"
    #i += 1
    #current = NextNonConstLevel_21_Desc(current, Q, W)
    #fo.write( s);

    
#print("There are"),
#print(i-1),
#print("non-constant (Q,W)-descriptions!")
#print("They are written to level_21.txt")


#fo.close()

#a = input()
print("input T")
T = Level_leq_2_Tree()
T.Input(0)
print("input Q")
Q = Level_leq_2_Tree()
Q.Input(0)
print("Computing.....")
psi = TensorProduct_22(T,Q)
print("number of (T,Q,*)-desc")
X = psi.domain
print(X.Cardinality())
W = LevelOneTree()
print("input W:")
W.Input(0)

xw = TensorProduct_21(X, W)
print("Number of (TQ, W)-desc:")
print(xw.cardinality)
qw = TensorProduct_21(Q, W)
qw_tree = qw.Domain()
print("Number of (Q,W)-desc:")
print(qw.cardinality)
tqw = TensorProduct_21(T, qw_tree)
print("Number of (T,QW)-desc:")
print(tqw.cardinality)
