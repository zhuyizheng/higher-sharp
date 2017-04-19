from copy import deepcopy
from sets import Set


def SingleMinusOne():      
    # creates (-1), a single node 
    return SingleNode([-1])
def DoubleMinusOne():
    # creates ((-1)), a double node
    return DoubleNode([SingleNode(-1)])

class SingleNode(object):
    ' a node in (*)^<omega'
    def __init__(self,entry = []):        #create a node in (*)^<omega
        
        self.entry = entry        #by default, the entry is empty sequence
    
    def Enumerate (self):       # Enumerate the entry of the node
        s = []
        for i in range (len(self.entry)):
                s .append(self.entry [i])
        return s
        
    def Output(self):
        if self.IsMinusOne():
            print(-1),
        else:
            o = '('
            for j in self.entry:
                o+=str(j)
                o+=' '
            if self.IsNonEmpty():
                o = o [:-1]
            o+=')'
            print(o),
         
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
        return SingleNode( self.entry[:-1])
        
    def Length(self):
        return len(self.entry)
        
    def Entry(self,k):
        if k>= self.Length():
            print ("This string is not that long!")
            return -2
        else:
            return self.entry[k]
 
    def MakeEntry(self,s):
        self.entry = s

    def Append( self, a):   # append a to the end
        return SingleNode( self.Enumerate + [a])
        
    def RestrictedTo(self, i):  #s restrcted to i
        return (SingleNode( s.entry[:i]))

        
        
    def LengthOfIntersection(self,s):        #the length of common part of self and s
    
        for i in range ( min(self.Length(), s.Length()) ):
            if self.Entry(i) != s.Entry(i):
                return i
        return min(self.Length(), s.Length())
    
    def Intersection(self,s):        #the intersection of self and s
        
        t = SingleNode()
        t.MakeEntry( s.entry[:self.LengthOfIntersection(s)] )
        return t  

    ####  reload operators    #####
    ####    by comparing the entries ###
    
    def __eq__(self,s):             #self == s
        return self.entry == s.entry
    
    def __ne__(self,s):             #self != s
        return not self==s
        
    def __lt__(self,s):              #self<s, the BK order
        
        k = self.LengthOfIntersection(s)
        t = self.Intersection(s)
        
        if t == self:
            return False
        if t == s:
            return True
        return self.entry[k]<s.entry[k]
    
    def __le__(self,s):             #self<=s, the BK order
        return self<s or self == s
    
    def __gt__(self,s):             #self > s
        return not self <= s
        
    def __ge__(self,s):             #self >= s
        return not self < s



class LevelOneNode(SingleNode):
    ' a node in omega^<omega with info to make a part of a level-1 tree'
    
    def __init__(self,entry = []):        #create a node in omega^<omega
        super(LevelOneNode, self).__init__(entry)
        
        self.parent = None
        self.number_of_children = 0
        self.first_child = None
        self.last_child = None
        self.left = None
        self.right = None
        self.BKleft = None
        self.BKright = None
        
    
    def IsLastBitLeftMost(self):    #is the last bit leftmost?
        return self.left is None
        
    def IsLastBitRightMost(self):    #is the last bit right most?
        return self.right is None
    
    def IsBKRightMost(self):        #is it BK right most?
        return self.BKright is None
    
    def IsBKLeftMost(self):            #is it BK left most?
        return self.BKleft is None


    def HasChild (self):            #does it have children?
        return self.number_of_children > 0
        
    def AddChild (self):            #add a child, returns the node of child
                
        current = LevelOneNode()
        
        current.entry = self.entry + [deepcopy(self.number_of_children)]
        
        current.parent = self
        
        self.number_of_children +=1
        
        if self.IsNonEmpty():
            current.BKright = self        
            
            if not self.IsBKLeftMost():
                current.BKleft = self.BKleft
                self.BKleft.BKright = current
            
            self.BKleft = current
        
        elif self.number_of_children > 1:
            current.BKleft = self.last_child
            self.last_child.BKright = current
        
        if self.number_of_children == 1:
            self.first_child = current
            self.last_child = current
        
        else:
            self.last_child.right = current
            current.left = self.last_child
        
        self.last_child = current
        
        return current
    
    def AddChildren (self, k):      #add k children, returns the node of the first new child
        
        if k == 0:
            return None
            
        new = self.AddChild()
        
        for i in range (1, k):
            self.AddChild()
            
        return new
        
    def MyChild (self, k):            #output my child indexed by k
        
        if k >=   self. number_of_children:
            
            print("This single node doesn't have these many children!")
            return None
            
        current = self.first_child
        
        for i in range (k):
            current = current.right
        
        return current
    
class LevelOneTree(object):
    'A level-1 tree, minus the empty node'
    
    def __init__(self):
        self.cardinality = 0
        self.root = LevelOneNode() 
        
    def Cardinality(self):
        return self.cardinality
        
    def SmallestNode(self):
        if self.IsEmpty():
            return None
        current = self.root
        while current.HasChild():
            current = current.first_child
        return current
    
    def GreatestNode(self):
        if self.IsEmpty():
            return None
        return self.root.last_child
    
    def IsSubtree (self, T):        #is self a subtree of T?
        
        if self.IsNonEmpty():
            return True
            
        current = self.root 
        expected = T.root 
        
        while True:
            
            if expected.number_of_children < current.number_of_children:
                return False
                
            if not current.HasChild():
                if current.IsEmpty():
                    return True
                while current.IsLastBitRightMost():
                    current = current.parent
                    expected = expected.parent
                    
                    if current.IsEmpty():
                        return True
                current = current.right
                expected = expected.right
            
            else:
                
                current = current.first_child
                expected = expected.first_child 
    
    def __eq__(self,T):
        return self.IsSubtree(T) and T.IsSubtree(self)
        
    def __ne__(self,T):
        return not self == T
    
    def IsEmpty(self):
        return not self.root.HasChild()
    
    def IsNonEmpty(self):
        return not self.IsEmpty()
    
    def ContainsElement (self, s):   #does it contain the element coded in the node s 
        
        if self.IsEmpty():
            
            return False
        
        if s.IsEmpty():
            return False            #an empty string is never in a level-1 tree
        
        #compare them bit by bit
        
        current = self.root
        
        for i in range(s.Length()):
            
            if current.number_of_children <= s.Entry(i):
                
                return False
            
            else:
                current = current.MyChild(s.Entry(i))
        
        return True
    
    def MyNode (self, s):    #return the node in me pointing to s
        
        if not self.ContainsElement(s):
            print("This node is not in the level-1 tree!")
            return None
        
        current = self.root
        
        for i in range(s.Length()):
            
            current = current.MyChild(s.Entry(i))
        
        return current

    def NodeOnRight (self,s):   #return the least node in me which is >_BK s
        
        current = self.SmallestNode()
        
        while current != self.GreatestNode():
            
            current = current.BKright
            
        if current > s:
        
            return current
            
        print("There is no node on the right in this single tree")
        return None
        
    def NodeOnLeft (self,s):   #return the least node in me which is <_BK s
        
        current = self.GreatestNode()
        
        while current != self.SmallestNode():
            
            current = current.BKleft

        if current < s:
            
            return current
            
        print("There is no node on the left in this single tree")
        return None
    
    def AddNodeBelow (self,s):  #add a node below s, returns the new node in the tree
        
        if s.IsEmpty():             # if empty sequence, add it
            
            self.cardinality += 1
                        
            return self.root.AddChild()
            
        if not self.ContainsElement(s): #if not empty sequence, it must be an element of s in the first place
            
            print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
            
            return None
            
        current = self.MyNode(s)
        
        self.cardinality += 1
        
        return current.AddChild()
        
    def AddNodesBelow (self,s, k): #add k nodes below s, returns the first new node in the tree
        
        if k==0:
            return None
        
        new = self.AddNodeBelow (s)
        
        for i in range (1,k):
            
            self.AddNodeBelow(s)
            
        return new
    
  
    def Input(self, d):      #input the tree on the screen
        
        self.cardinality = 0
        
        current = self.root
                
        while True:
    
            for i in range(d):
                print(" "),
            
            print ("Input the level-1 tree, immediate successors of"), 
            current.Output() 
            print (": "),
                    
            
            k = input()
    
                    
            if k == 0:
                
                if current.IsEmpty():
                    
                    return
                    
                while current.IsLastBitRightMost():
                    
                    current = current.parent
                    
                    if current.IsEmpty():
                    
                        return
                        
                current = current.right
                
            else:
                    
                self.AddNodesBelow(current,k)
                
                current = current.first_child

                
    def Enumerate (self):   #enumerate the nodes, NOT IN THE BK ORDER! in a way that every initial segment must form a subtree
        
        t = []
        
        if self.IsEmpty():
            return t
            
        current = self.root.first_child
        
        while current != self.root:
            
            t .append(current)
            
            if current.HasChild():
                
                current = current.first_child
                
            else:
                
                while current.IsNonEmpty() and current.IsLastBitRightMost():
                    
                    current = current.parent
                
                if current.IsEmpty():
                    
                    return t
                    
                else:
                    
                    current = current.right
        
    def IsRegular(self):
        return self.root.number_of_children <= 1
        
    def Rank(s):            # the BK-rank of s in the tree 
        
        if not self.ContainsDoubleElement(s):
            print("This node doesn't belong to the tree! No rank!")
            return None
            
        i = 0
        current = self.SmallestNode()
        
        while ( current != s):
            i += 1
            current = current.BKright
        return i

class DoubleNode (LevelOneNode):
    ' a node in ((*)^<omega)^<omega'
    
    def __init__(self,entry = []):        #create a node in omega^<omega
        
        super(DoubleNode,self).__init__(entry)
        self.immediate_extensions = LevelOneTree() #the set of s such that self+[s] is in the tree
    
    def Minus(self):        #outputs self^-
        
        t = DoubleNode()
        t.MakeEntry(self.entry[:-1])
        return t

    def AddChildBelow (self, s):            #add a child below the single node s, returns the new child
        
        if not s.IsEmpty():
            if not self.immediate_extensions.ContainsElement(s):
                print ("s is nonempty and not the last entry in the immediate extension! Impossible to add a child!")
                return None
        
        self.number_of_children += 1
        #number_of_children + 1
        
        single = self.immediate_extensions.AddNodeBelow(s) 
        #single is the extension of s to be added
        
        if s.IsNonEmpty():
            current = self.MyChild(s)
        else:
            current = self
        #current is the BK next of the new node
        
        new = DoubleNode()
        new.entry = self.entry + deepcopy([single])
        new.parent = self
        #create a new node whose entry extends by s, parent point to self
        
        
        if not current.IsBKLeftMost():      #if current is not BKleftmost,
                                            #its left and itself has new in between
            new.BKleft = current.BKleft     #assign the left of new and vice versa
            current.BKleft.BKright = new
            
                                            #otherwise, nothing to do
            
        new.BKright = current       #the right of the new node must be current
        current.BKleft = new        #assign them under all cases

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
            
            new.left = current.BKleft
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

    def AddLevelOneTreeChildren (self, P):          #add children that forms a level-1 tree P, only when it has no children, and returns the first child
        if self.HasChild():
            print("This double node already has children!")
            return None
        
        if P.IsEmpty():
            return None
        
        emptysinglenode = SingleNode()
        new = self.AddChildBelow(emptysinglenode)
                
        t = P.Enumerate()
        
        for i in range (1,P.cardinality):
            u = deepcopy(t[i])
            u.MakeEntry ( u.Enumerate()[:-1])
            self.AddChildBelow (u)
            del u
            
        return new
         
    def MyChild (self, s):            #output my child indexed by s
        
        if not self.immediate_extensions.ContainsElement(s):
            
            print("This double node doesn't have this child!")
            return None
            
        current = self.first_child
        
        for i in range (self.number_of_children):
            if current.entry[-1] == s:
                return current
            else:
                current = current.right
    
    def Output(self):
        if self.IsMinusOne():
            print(-1),
        else:
            print("("),
            for s in self.Enumerate():
                s.Output()
            print(")"),
    
class DoubleTree(object):
    'A tree on omega^<omega, minus the empty node'
    
    def __init__(self):
        self.cardinality = 0
        self.root = DoubleNode() 
        
    def Cardinality(self):
        return self.cardinality
    
    def MyDoubleNode (self, s):    #return the node in me pointing to s
        
        if not self.ContainsDoubleElement(s):
            print("This double node is not in the double tree!")
            return None
        
        current = self.root
        
        for i in range(s.Length()):
            
            current = current.MyChild(s.Entry(i))
        
        return current
    
        
        if not self.ContainsDoubleElement(s):
            print("This node is not in the level-1 tree!")
            return None
        
        current = self.root
        
        for i in range(s.Length()):
            
            current = current.MyChild(s.Entry(i))
        
        return current
    
    def IsSubtree (self, T):        #is self a subtree of T?
        
        if self.IsNonEmpty():
            return True
            
        current = self.root 
        expected = T.root 
        
        while True:
            
            if not current.immediate_extensions.IsSubtree(expected.immediate_extensions):
                return False
                
            if not current.HasChild():
                if current.IsEmpty():
                    return True
                while current.IsLastBitRightMost():
                    current = current.parent
                    expected = expected.parent
                    
                    if current.IsEmpty():
                        return True
                current = current.right
                expected = expected.right
            
            else:
                
                current = current.first_child
                expected = expected.first_child 
    
    def __eq__(self,T):
        return self.IsSubtree(T) and T.IsSubtree(self)
        
    def __ne__(self,T):
        return not self.__eq__(T)
    
    def IsEmpty(self):
        return not self.root.HasChild()
    
    def IsNonEmpty(self):
        return not self.IsEmpty()
    
    def ContainsDoubleElement (self, s):    
        
        if self.IsEmpty():
            
            return False
        
        if s.IsEmpty():
            return False            #an empty string is never in a double tree
            
        #compare them bit by bit
        
        current = self.root
        
        for t in s.Enumerate():
            
            if not current.immediate_extensions.ContainsElement(t):
                
                return False
            
            else:
                current = current.MyChild(t)
        
        return True
    
    def MyDoubleNode(self, s):    #return the double node in me pointing to s
        
        if not self.ContainsDoubleElement(s):
            print("This double node is not in the double tree!")
            return None
        
        current = self.root
        
        for t in s.Enumerate():
            
            current = current.MyChild(t)
        
        return current

    def NodeOnRight (self,s):   #return the least node in me which is >_BK s
        
        current = self.SmallestNode()
        
        while current != self.GreatestNode():
            
            current = current.BKright
            
        if current > s:
            
            return current
            
        print("There is no node on the right in this double tree")
        return None
        
    def NodeOnLeft (self,s):   #return the least node in me which is <_BK s
        
        current = self.GreatestNode()
        
        while current != self.SmallestNode():
            
            current = current.BKleft
            
        if current < s:
            
            return current
            
        print("There is no node on the left in this double tree")
        return None
    
    def AddDoubleNodeBelow (self,s):  #add a double node below s, returns the new double node in the tree
        
        if s.IsEmpty():             # if empty sequence, add it
            
            self.cardinality += 1
                        
            return self.root.AddChild()
            
        if not self.ContainsDoubleElement(s): #if not empty sequence, it must be an element of s in the first place
            
            print ("This double sequence is not empty, not in the tree. Impossible to add a node below in the double tree")
            
            return None
            
        current = self.MyDoubleNode(s)
        
        self.cardinality += 1
        
        return current.AddChild()
        
    def AddLevelOneTreeBelow (self,s, P): #add nodes below s that forms a level-1 tree P, returns the first new node in the tree
        
        if P.IsEmpty():
            return None
        
        if s.IsEmpty():
            
            self.cardinality += P.Cardinality()
            
            return self.root.AddLevelOneTreeChildren(P)
        
        if not self.ContainsDoubleElement(s): #if not empty sequence, it must be an element of s in the first place
            
            print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
            
            return None
            
        current = self.MyDoubleNode(s)
                
        self.cardinality = self.cardinality + P.Cardinality()
            
        return current.AddLevelOneTreeChildren(P)
    
    def Input(self, d):      #input the doubletree on the screen
        
        self.cardinality = 0
        
        current = self.root
                
        while True:
            
            for i in range(d):
                print(" "),
            
            print ("Input the double tree, immediate successors of"), 
            current.Output(),
            print (": ")
            
            K = LevelOneTree()
            K.Input(d+1)
            
            if K.IsEmpty():
                
                if current.IsEmpty():
                    
                    return
                    
                while current.IsLastBitRightMost():
                    
                    current = current.parent
                    
                    if current.IsEmpty():
                    
                        return
                        
                current = current.right
                
            else:
                    
                self.AddLevelOneTreeBelow(current,K)
                    
                current = current.first_child

    def Enumerate (self):   #enumerate the nodes, NOT IN THE BK ORDER! in a way that every initial segment must form a subtree
        
        t = []
        
        if self.IsEmpty():
            return t
            
        current = self.root.first_child
        
        while current != self.root:
            
            t.append(current)
            
            if current.HasChild():
                
                current = current.first_child
                
            else:
                
                while current.IsNonEmpty() and current.IsLastBitRightMost():
                    
                    current = current.parent
                
                if current.IsEmpty():
                    
                    return t
                    
                else:
                    
                    current = current.right
        
class PartialLevelOneTree(object):
    
    def __init__(self, tree = LevelOneTree(), node = SingleNode ([0])):     #by default, assign it the empty tree and the node with entry (0)
        
        self.tree = tree
        self.node = node

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
        P.AddNodeBelow (p.Minus())
        return P
    
    def Cardinality(self):
        return self.tree.Cardinality() + 1
        
    def UniformCofinality(self):
        
        if self.Degree() == 0:
            return -1
        return self.node.Minus()

    def __eq__(self,s):
        return self.tree == s.tree and self.node == s.node
    def __ne__(self,s):
        return not self == s
    
    def IsPartialSubtree (P):
        if self.Degree() == 0:
            return False
        return self.Completion().IsSubtree(P)

def MakePartialLevelOneTree (P):            ## makes a list of partial level-1 trees whose tree component is P
    
    if not P.IsRegular():
        print("This level-1 tree is not regular. Cannot extend to a partial level-1 tree.")
        return None
    
    
    if P.IsEmpty():
        
        return [PartialLevelOneTree()]
        
    else:
        
        t = [PartialLevelOneTree( P, SingleMinusOne() ) ]
        
        for ee in P.Enumerate():
            
            t.append( PartialLevelOneTree( P, SingleNode( ee.Enumerate() + [ee.number_of_children] )  ) )
        
        return t

def EnumerateNodesOfPartialLevelOneTree(P):    # makes a list of the nodes of partial level-1 trees whose component is P
    
    if P.IsEmpty():
        return [SingleMinusOne()]
    
    t = MakePartialLevelOneTree(P)
    u = []
    for ee in t:
        u.append(ee.node)
    
    return u

def OutputNodesOfPartialLevelOneTree(P):    # print the nodes of partial level-1 trees whose component is P on the screen

    u = EnumerateNodesOfPartialLevelOneTree(P)
    for s in u:
        s.Output()
        
class AttrLevelOneNode(LevelOneNode):
    'A node in (omega x something)^{<omega}'
    
    def __init__(self, entry = []):
        
        super(AttrLevelOneNode,self).__init__(entry)
        self.image = None
        
    def Variable(self):
        return self.entry
    def Image(self):
        return self.image
        
    def MakeImage(self, image):
        self.image = image
            
    def LengthOfIntersection(self,s):        #the length of common part of self and s
    
        for i in range ( min(self.Length(), s.Length()) ):
            if self.entry[i] != s.entry[i] or self.image[i] == s.image[i]:
                return i
        return min(self.Length(), s.Length())
    
    def Intersection(self,s):        #the intersection of self and s
        
        t = AttrLevelOneNode()
        t.entry = s.entry[:self.LengthOfIntersection(s)]
        t.image = s.image[:self.LengthOfIntersection(s)]
        return (t)   


    def AddChild (self, y):            #add a child, with value y, returns the node of child
                
        current = AttrLevelOneNode()
        
        current.entry = self.entry + [deepcopy(self.number_of_children)] 
        current.image = self.image + [y]
        
        current.parent = self
        
        self.number_of_children +=1
        
        if self.IsNonEmpty():
            current.BKright = self        
            
            if not self.IsBKLeftMost():
                current.BKleft = self.BKleft
                self.BKleft.BKright = current
            
            self.BKleft = current
        
        elif self.number_of_children > 1:
            current.BKleft = self.last_child
            self.last_child.BKright = current
        
        if self.number_of_children == 1:
            self.first_child = current
            self.last_child = current
        
        else:
            self.last_child.right = current
            current.left = self.last_child
        
        self.last_child = current
        
        return current
    
    
    def __eq__(self,s):             #self == s
        return self.entry == s.entry and self.image == s.image
    
    def __ne__(self,s):             #self != s
        return not self==s

class AttrLevelOneTree(LevelOneTree):
    'A template for level-1 factoring, level-121-factoring'
    
    def __init__(self):
        super(AttrLevelOneTree,self).__init__()
        self.root = AttrLevelOneNode()
    
    def IsSubtree (self, T):        #is self a subtree of T?
        
        current = self.root 
        expected = T.root 
        
        while True:
            
            if not current.HasChild():
                if current.IsEmpty():
                    return True
                while current.IsLastBitRightMost():
                    current = current.parent
                    expected = expected.parent
                    
                    if current.IsEmpty():
                        return True
                current = current.right
                expected = expected.right
            
            else:
                if not expected.HasChild():
                    return False
                current = current.first_child
                expected = expected.first_child 
                while not expected.IsLastBitRightMost:
                    if current == expected:
                        break
                if current != expected:
                    return False
                    
    def __eq__(self,T):
        return self.IsSubtree(T) and T.IsSubtree(self)
        
    def __ne__(self,T):
        return not self == T
    
    def IsTrivial(self):        #is the tree trivial, i.e. nothing extending emptyset?
        # just equivalent to the IsEmpty definition
        return self.root.number_of_children == 0
    
    def IsNonTrivial(self):
        return not self.IsTrivial()
    
    def ContainsElementWithValue (self, s, y):   #is s NONEMPTY AND a member of T and y is the image of s? (by default, emptyset is not in any tree) 

        if self.IsTrivial():
            return False
        
        if s.IsEmpty():
            return False            #an empty string is never in a tree
            
        #compare them bit by bit
        
        current = self.root
        
        for i in range(s.Length()):
            
            current = current.first_child
            
            while not current.IsLastBitRightMost():
                
                if current.entry == s and current.image == y:
                    break
                current = current.right
                    
            if not (current.entry == s and current.image == y):
                return False
        
        return True
    
    def AddNodeBelowWithValue (self,s, y):  #add a node below s in the domain with value y, returns the new node in the tree
        
        if s.IsEmpty():             # if empty sequence, add it
            
            self.cardinality += 1
                        
            new =  self.root.AddChild(y)
            
            self.domain.AddChildBelow(s)
            
            return new
            
        if not self.ContainsElement(s): #if not empty sequence, it must be an element of s in the first place
            
            print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
            
            return None
            
        current = self.MyNodeAtDomain(s)
        
        self.cardinality += 1
        
        new = current.AddChild(y)
        
        self.domain.AddChildBelow(s)
        
        return new
    
    def MyNodeAtDomain (self, s):    #return the node in me pointing to s
        return self.MyNode(s)
    
    def Value(self,s):              #returns the value at s 
        
        d = self.MyNodeAtDomain(s)
        return d.image

    def MakeValue(self,s,y):          #make the value at s y
        
        d = self.MyNodeAtDomain(s)
        d.image = y
    
class AttrDoubleNode (AttrLevelOneNode, DoubleNode):
    'A node in (omega^<omega x something)^{<omega}'
            
    
    def Intersection(self,s):        #the intersection of self and s
        
        t = AttrDoubleNode()
        t.entry = s.entry[:self.LengthOfIntersection(s)]
        t.image = s.image[:self.LengthOfIntersection(s)]
        return (t)   
    
class AttrDoubleTree (AttrLevelOneTree, DoubleTree):
    'A template for level-2 tree, level-3 tree, level-222-factor, etc'
    
    def __init__(self):
        super(AttrDoubleTree,self).__init__()
        root = AttrDoubleNode()
        
    def EnumerateDomain(self):
        return DoubleTree.Enumerate(self)

    def AddDoubleNodeBelowWithValue (self,s, y):  #add a double node below s in the domain with value y, returns the new node in the tree
        
        if s.IsEmpty():             # if empty sequence, add it
            
            self.cardinality += 1
                        
            new =  self.root.AddChild(y)
            
            self.domain.AddChildBelow(s)
            
            return new
            
        if not self.ContainsDoubleElement(s): #if not empty sequence, it must be an element of s in the first place
            
            print ("This single sequence is not empty, not in the tree. Impossible to add a node below in the level-1 tree")
            
            return None
            
        current = self.MyDoubleNodeAtDomain(s)
        
        self.cardinality += 1
        
        new = current.AddChild(y)
        
        self.domain.AddChildBelow(s)
        
        return new
    
    def MyDoubleNodeAtDomain (self, s):    #return the node in me pointing to s
        return self.MyDoubleNode(s)
    
    def DoubleValue(self,s):              #returns the value at s 
        
        d = self.MyDoubleNodeAtDomain(s)
        return d.image

    def MakeDoubleValue(self,s,y):          #make the value at s y
        
        d = self.MyDoubleNodeAtDomain(s)
        d.image = y
    
class LevelTwoTree(AttrDoubleTree):
    'a level-2 tree'

    def __init__(self):
        
        super(LevelTwoTree,self).__init__()
        self.root = AttrDoubleNode()
        self.root.image = PartialLevelOneTree()
        cardinality = 1
        
    def DoubleValue(self, s):
        if s.IsNonEmpty():
            return AttrDoubleTree.DoubleValue(self, s)
        return self.root.image
        
    def Input(self,d):
        
        for i in range(d):
            print(" "),
        
        print ("Input the level-2 tree:")
        
        DoubleTree.Input(self,d+1)
        
        e = self.EnumerateDomain()
        
        for ee in e:
            
            partial = self.DoubleValue(ee.Minus())
            completion = partial.Completion()
            partial_extend = MakePartialLevelOneTree(completion)
            partial_extend_node = EnumerateNodesOfPartialLevelOneTree(completion)
            
            print "Possible values of the node component at", 
            ee.Output() 
            print ":"
            
            for i in range(len(partial_extend_node)):
                print i+1, ". ", 
                partial_extend_node[i].Output()
                print " "

            for i in range(d):
                print(" "),
            
            k = input("which one? ")
            
            self.MakeDoubleValue(ee,partial_extend[k-1])
        
        print("Level-2 tree input complete!")    
    
    def ContainsInDomain(self,s):               # does dom(self) contain the double node s?
        if self.ContainsDoubleElement(s):
            return True
        if s.IsEmpty():     # empty set is always in the domain
            return True
        return False
        
    def ContainsInDomainStar(self,s):       #does dom^*(self) contain the double node s?
        if self.ContainsInDomain(s):
            return True
        if s.IsMinusOne():  #(-1) is always in the extended domain
            return True
        if s.IsContinuousType() and self.ContainsDoubleElement(s.Minus()):
            return True
        return False
    
    def GetPartialLevelOneTower(self,s):    #outputs the Q[s], the partial level <=1 tower of discontinuous type, for s in dom^*(Q)
       
        if self.ContainsInDomain(s):        #when s in dom(Q), the output is of discontinous type
            t = PartialLevelOneTower()
            for i in range(s.Length()):
                t.AppendPartialTree( self.Value( s.RestrictedTo(i)) )  
            return t
            
        if self.ContainsInDomainStar(s):    #when s in dom*(Q)\dom(Q), the output is of continous type
            t = self.GetPartialLevelOneTower( s.Minus())
            t.AppendCompletion()
            return t
            
 
    
class PartialLevelOneTower:
    'partial level <=1 tower'
    #we don't define potential partial level <=1 tower, as it is 
    #easily coded in a partial level <=1 tower
    
    def __init__(self, tree_sequence = [LevelOneTree()], node_sequence = [(0)]):
    #
    # by default, it constructs ([empty],[(0)]), which is Q([0]) for any level-2 tree Q
    #
        
        self.tree_sequence = tree_sequence
        self.node_sequence = node_sequence
    
    def IsContinuousType(self):
        return len(self.tree_sequence) == len(self.node_sequence)+1
    
    def IsDiscontinuousType(self):
        return len(self.tree_sequence) == len(self.node_sequence)
    
    def TreeLength(self):
        return len(self.tree_sequence)
    def NodeLength(self):
        return len(self.node_sequence)
    
    def Tree(self, i):
        if i < self.TreeLength():
            print("This partial level-1 tower does not have so many trees!")
            return
        return self.tree_sequence[i]
        
    def Node(self, i):
        if i < self.NodeLength():
            print("This partial level-1 tower does not have so many node!")
            return
        return self.node_sequence[i]
    
    
    def Signature(self):                    #signature
        if self.IsDiscontinuousType():
            return self.node_sequence [:-1]
        else:
            return self.node_sequence
    
    def LastTree(self):
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
            return self.LastPartialTreeWhenDiscontinuous().Completion
            
    def AppendCompletion(self):      #append the comletion to make it continous type
        self.tree.append( self.Completion())
    
    def AppendPartialTree(self, P): #append a partial tree to discontinuous type. The result remains discontinous type
        if self.IsDiscontinuousType():
            self.tree_sequence.append( P.tree )
            self.node_sequence.append( P.node )
    
    def Decapped(self):             # when continuous type, outputs the one without the last tree
        return PartialLevelOneTower(   self.tree_sequence[:-1]  , self.node_sequence)
    
    def Completed(self):            #when discontinous type, outputs the one with a completion attached
        return PartialLevelOneTower(   self.tree_sequence + [ self.Completion]  , self.node_sequence)
        
    def __eq__(self, PP):
        return self.tree_sequence == PP.tree_sequence and self.node_sequence == PP.node_sequence
        
    def __ne__(self,PP):
        return not self == PP
        
#    def __lt__(self,PP):        #self is a proper initial segment of PP
            
        
    
class LevelOneFactor (AttrLevelOneTree):
    'level-1 factoring map'
    ##(empty,empty) is not a node in this paper. We just make it a node for convenience
    
    def __init__(self):
        super(LevelOneFactor,self).__init__()
        self.root.MakeValue( SingleNode() )
        
    def IsFactor(self):     # is it a level-1 factoring map?
        if self.IsEmpty():
            return True
        current = self.SmallestNode()
        while (current.BKright != self.GreatestNode()):
            if self.Value(current) >= self.Value(current.BKright):
                return False
        if self.Value(current) >= self.Value(current.BKright):
            return False
        return True
    
    def IsFactorInto(self, W):      # is it a level-1 factoring map into W?
        if self.IsEmpty():
            return True
        if not self.IsFactor():
            return False
        current = self.SmallestNode()
        while (current.BKright != self.GreatestNode()):
            if not W.ContainsElement(self.Value(current)):
                return False
        if not W.ContainsElement(self.Value(current)):
            return False
        return True
    
    def ContainsInRange(self, s):   #does s belong to the range?
        
        if self.IsTrivial():
            return False
            
        current = self.SmallestNode()
        while (current.BKright != self.GreatestNode()) : 
            if s == self.Value (current) :
                return True
            s = s.BKright
        if s == self.Value (current) :
            return True
        return False
        
        

class Level_leq_2_Node:     
    'a node of the form (1,q), q in omega^<omega, or (2,q), q in omega^{omega^<omega}'
    
    def __init__(self, degree = 2, node = DoubleNode()):
        self.degree = degree
        self.node = node
    
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
        else:
            return self.node < q.node
    def __le__(self,q):
        return self < q or self == q
    def __ge__(self,q):
        return not self < q
    def __gt__(self,q):
        return not self <= q
                
class Level_leq_2_Tree:
    
    def __init__(self, tree_1 = LevelOneTree(), tree_2 = LevelTwoTree()):
        self.tree_1 = tree_1
        self.tree_2 = tree_2
    
    def Level_1_Component (self):
        return self.tree_1
    
    def Level_2_Component (self):
        return self.tree_2
    
    def Cardinality(self):
        return self.tree_1.Cardinality() + self.tree_2.Cardinality()
    
    def ContainsInDomain(self,q):        #does the tree contain q in its domain?
        if q.Degree() == 1:
            return self.tree_1.ContainsElement(q.Node())
        if q.Degree() == 2:
            return self.tree_2.ContainsDoubleElement(q.Node())
    
    def Value(q):                       #when q is of degree 2 and in its domain, output its value. otherwise None.
        if q.Degree()==2 and self.ContainsElementInDomain(q):
            return self.tree_2.Value(q.Node())
            
    def ContainsInDomainStar(self,q):    # does the tree contain q* in its domain?
        if self.ContainsElementInDomain(q):
            return true
        if q.Degree == 2 and self.tree_2.ContainsInDomainStar(q.node):
            return true
        return False
    
    def GetPartialLevelOneTower(self,q):    #outputs the 2Q[q] , the partial level <=1 tower
        if q.Degree() == 2:
            return self.tree_2.GetPartialLevelOneTower(q.Node())
    
    def __eq__(self, Q):
        return self.tree_1 == Q.tree_1 and self.tree_2 == Q.tree_2
    def __ne__(self, Q):
        return not self == Q
    
class LevelTwoDescription:
    
    def __init__(self, node = DoubleNode(), partial_tower = PartialLevelOneTower() ):
        #by default, it generates the constant level-2 description:
        #(empty, empty, (0))
        
        self.node = node
        self.partial_tower = partial_tower
        
    def IsContinuousType(self):
        return self.node.IsContinuousType()
        
    def IsDiscontinuousType(self):
        return self.node.IsDiscontinuousType()
        
    def IsConstant(self):               # is it the constant level-2 desc?
        return self.node.IsEmpty()
        
    def AppendMinusOne(self):           # if discontinous type, append the node by -1 and complete the partial tower
        self.node.append(DoubleMinusOne())
        self.partial_tower.AppendCompletion()
    
    def __eq__(self,D):
        return self.node == D.node and self.partial_tower == D.partial_tower 
    def __ne__(self,D):
        return not self == D
        
    def LengthOfNode(self):
        return self.node.Length()
    def Node(self):
        return self.node
    def PartialTower(self):
        return self.partial_tower
 #   def LengthOfPartialTower(self):
  #      return self.partial_tower.Length()
    
    def Node_2(self,i):
        return self.node.Entry(i)
    def Node_1(self,i):
        return self.partial_tower.Node(i)
        
    def Represent(self):            #<q>, to compare the BK orders
        
        r = SingleSequence()
        k = self.LengthOfNode()
        P = self.partial_tower.LastTree()
        
        if self.node.IsContinuousType():
            for i in range (k-1):
                r . Append (  P.Rank( self.partial_tower.Node(i) ) )
                r . Append ( self.node.Entry(i))
            r.Append(-1)
        else:
            for i in range (k):
                r . Append (  P.Rank( self.partial_tower.Node(i) ) )
                r . Append ( self.node.Entry(i))
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

    def Is_2_Desc(self, Q):         # is it a Q-desc?
        if not Q.ContainsInDomainStar(self.node):
            return False
        if self.partial_tower != Q.GetPartialLevelOneTower(self.node):
            return False
        return True
    
        

class Level_leq_2_Description:
    'level <=2 description'
    
    def __init__ (self, degree = 2, desc = LevelTwoDescription() ):
        #by default, it generates (2, the constant level-2 desc)
        self.degree = degree
        self.desc = desc
        
    def IsContinuousType(self):
        if self.degree == 2:
            if self.desc.IsContinuousType():
                return True
        return False

    def IsDiscontinuousType(self):
        return not self.IsContinuousType()

    def IsContinuousType(self):
        if self.degree == 2:
            if self.desc.IsContinuousType():
                return True
        return False
    
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
        return self.desc < D.desc 
    def __le__(self,D):
        return self < D or self == D
    def __ge__(self,D):
        return not self < D
    def __gt__(self,D):
        return not self <= D
    
def OplusTwo(q, sigma):         #q oplus sigma, where q is in a level-2 tree
    t = SingleNode()
    k = q.LengthOfNode()
    for i in range(k):
        t.Append(sigma.Value(q.Node_1(i)))
        t.Append(q.Node_2(i))
    return t
    

class Level_21_Description:
    'level-(2,1)-description'
    #
    # (d,q,sigma), where d in {1,2}, q is a Q-desc, sigma factors (P,W)
    #
    
    def __init__(self):
        self.degree = 2
        self.desc = LevelTwoDescription()
        self.factor = LevelOneFactor()
    #the default one is constant
    
    
    def Is_2_Desc(self, Q):     # is it a Q-desc? 
        
        if not self.factor.IsFactor():
            return False
            
        if self.degree == 2:
            return self.desc.Is_2_Desc(Q.Level_2_Component())
        
        if self.factor.IsNonTrivial():
            return False
            
        return Q.Level_1_Component.ContainsElement(self.desc)
        
    def Is_21_Desc(self, Q,W):  # is it a (Q,W)-desc?
        if not self.Is_2_Desc(Q):
            return False
        return self.factor.IsFactorInto(W)
        
    def Degree(self):           # its degree
        return self.degree
    
    def Sign_1 (self):          # its level-1 signature
        if self.degree == 1:
            return []
        t = SingleNode()
        k = self.desc.LengthOfNode()
        for i in range(k):
            t.Append(self.factor.Value(q.Node_1(i)))
        return t
    
    def IsContinuousType_1 (self):    # is it level-1 continuous type?
        if self.degree == 2:
            if self.desc.IsContinuousType():
                return True
        return False
    
    def IsDiscontinuousType_1 (self):   # is it level-1 discontinuous type?
        return not self.IsContinuousType_1()
        
    def UCF_1 (self):       #ucf_1(D)
        if d == 1:
            return -1
        if d == 2 and self.desc.partial_tower.UniformCofinality() == -1:
            return -1
        return self.factor.Value( self.desc.partial_tower.UniformCofinality() )
        
    def Sign_2 (self):      # its level-2 signature
        
        s = []
        q = self.desc
        k = q.LengthOfNode
        
        if self.degree == 1:
            s.append( Level_leq_2_Node ( 1 , q))
            return s
        
        if q.IsContinuousType():
            for i in (1, k):
                s.append(  Level_leq_2_Node(2, q.Node() ))
        else:
            for i in (1, k+1):
                s.append(  Level_leq_2_Node(2, q.Node() ))
        return s
    
    def IsContinuousType_2 (self,W):  # is it level-2 W continuous type?
        if self.degree == 1:
            return False
        if self.desc.partial_tower.UniformCofinality() == -1:
            return True
        if self.UCF_1() == W.SmallestNode():
            return True
        if self.factor.ContainsInRange( W.NodeOnLeft(  self.UCF_1() ) ):
            return True
        return False

    def IsDiscontinuousType_2 (self,W): 
        return not self.IsContinuousType_2(W)
        
    def UCF_2 (self,W):         #the level-2 W-uniform cofinality
        
        d = self.degree
        q = self.desc 
        
        if d == 1:
            return Level_leq_2_Node ( 1 , q)
        if q.IsContinuousType():
            if self.IsContinuousType_2 (W):
                return Level_leq_2_Node(2, LevelTwoDescription ( q.Node().Minus(), q.PartialTower().Decapped()))
            else:
                return Level_leq_2_Node(2, LevelTwoDescription ( q.Node().Minus(), q.PartialTower()))
        else:
            if self.IsContinuousType_2 (W):
                return self
            else:
                return Level_leq_2_Node(2, LevelTwoDescription ( q.Node(), q.PartialTower().Completed()))
                
    def IsConstant(self):          #is it the constant level-21-desc?
        if self.degree == 2:
             if self.desc.IsConstant():
                return True
        return False
        
                 
                 
         
P = LevelTwoTree()
P.Input(0)


