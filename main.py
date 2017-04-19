from copy import deepcopy

class SingleNode:
    ' a node in (*)^<omega'
    def __init__(self):        #create a node in (*)^<omega
        
        self.entry = []        #by default, the entry is empty sequence
    
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
            if self.IsNonempty():
                o = o [:-1]
            o+=')'
            print(o),
         
    def IsEmpty(self):
        return len(self.entry) == 0

    def IsNonempty(self):
        return not self.IsEmpty()
        
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
 
    def IsMinusOne(self):               # is it (-1)? 
        if self.Length() != 1:
            return False
        elif type(self.Entry(0)) is int:
            if self.Entry(0) == -1:
                return True
        else:
            return False
        
        
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
    
    def __init__(self):        #create a node in omega^<omega
        SingleNode.__init__(self)
        
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
        
        if not self.IsEmpty():
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
    
class LevelOneTree:
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
        
        if not self.IsEmpty():
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
            
            t = t + [current]
            
            if current.HasChild():
                
                current = current.first_child
                
            else:
                
                while (not current.IsEmpty()) and current.IsLastBitRightMost():
                    
                    current = current.parent
                
                if current.IsEmpty():
                    
                    return t
                    
                else:
                    
                    current = current.right
        
    def IsRegular(self):
        return self.root.number_of_children <= 1

class DoubleNode (LevelOneNode):
    ' a node in ((*)^<omega)^<omega'
    
    def __init__(self):        #create a node in omega^<omega
        
        LevelOneNode.__init__(self)
        self.immediate_extensions = LevelOneTree() #the set of s such that self+[s] is in the tree

    def AddChildBelow (self, s):            #add a child below the single node s, returns the new child
        
        if not s.IsEmpty():
            if not self.immediate_extensions.ContainsElement(s):
                print ("s is nonempty and not the last entry in the immediate extension! Impossible to add a child!")
                return None
        
        self.number_of_children += 1
        #number_of_children + 1
        
        single = self.immediate_extensions.AddNodeBelow(s) 
        #single is the extension of s to be added
        
        if not s.IsEmpty():
            current = self.MyChild(s)
        else:
            current = self
        #current is the BK next of the new node
        
        new = DoubleNode()
        new.entry = self.entry + deepcopy([single])
        new.parent = self
        #create a new node whose entry extends by s, parent point to self
        
        if (not self.IsEmpty()) or (not s.IsEmpty()):
            if not current.IsBKLeftMost():
                
                new.BKleft = current.BKleft
                current.BKleft.BKright = new
            
            new.BKright = current
            current.BKleft = new
        elif self.number_of_children > 1:
            new.BKleft = self.last_child
            self.last_child.BKright = new
        #assign the BK order
        
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
            
        elif not s.IsEmpty():
            
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

    def AddChildren (self, P):          #add children that forms a level-1 tree P, only when it has no children, and returns the first child
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
            
            print("This double node doesn't have this children!")
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
            for s in self.Enumerate():
                s.Output()
    
class DoubleTree:
    'A tree on omega^<omega, minus the empty node'
    
    def __init__(self):
        self.cardinality = 0
        self.root = DoubleNode() 
        
    def Cardinality(self):
        return self.cardinality
    
    def IsSubtree (self, T):        #is self a subtree of T?
        
        if not self.IsEmpty():
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
    
    def ContainsElement (self, s):    
        
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
    
    def MyNode(self, s):    #return the node in me pointing to s
        
        if not self.ContainsElement(s):
            print("This node is not in the double tree!")
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
        
    def AddNodesBelow (self,s, P): #add nodes below s that forms a level-1 tree P, returns the first new node in the tree
        
        if P.IsEmpty():
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
                    
                self.AddNodesBelow(current,K)
                    
                current = current.first_child

    def Enumerate (self):   #enumerate the nodes, NOT IN THE BK ORDER! in a way that every initial segment must form a subtree
        
        t = []
        
        if self.IsEmpty():
            return t
            
        current = self.root.first_child
        
        while current != self.root:
            
            t = t + [current]
            
            if current.HasChild():
                
                current = current.first_child
                
            else:
                
                while (not current.IsEmpty()) and current.IsLastBitRightMost():
                    
                    current = current.parent
                
                if current.IsEmpty():
                    
                    return t
                    
                else:
                    
                    current = current.right
        
class PartialLevelOneTree:
    
    def __init__(self):     #by default, assign it the empty tree and the node with entry (0)
        
        self.tree = LevelOneTree()
        s = SingleNode()
        s.MakeEntry([0])
        self.node = s

    def IsContinuousType (self):
        return self.node.IsMinusOne()
    
    def IsDiscontinuousType (self):
        return not self.IsContinuousType()
        
    def Tree(self):
        return self.tree
        
    def Node(self):
        return self.node
        
    def Completion(self):
        if self.IsContinuousType:
            print("This partial level <=1 tree is of continuous type, no completion!")
            return None
        P = deepcopy(self.tree)
        p = deepcopy(self.node)
        p_minus = SingleNode()
        p_minus.MakeEntry( p.Enumerate [ : p.Length() - 1 ] )
        P.AddNodeBelow (p_minus)
        
    def UniformCofinality(self):
        
        if IsContinuousType:
            return -1
        p_minus = SingleNode()
        p_minus.MakeEntry( p.Enumerate [ : p.Length() - 1 ] )
        P.AddNodeBelow (p_minus)

    def __eq__(self,s):
        return self.tree == s.tree and self.node == s.node
    def __ne__(self,s):
        return not self == s

def MakePartialLevelOneTree (P):            ## makes a list of partial level-1 trees whose tree component is P
    
    if not P.IsRegular():
        print("This level-1 tree is not regular. Cannot extend to a partial level-1 tree.")
        return None
    
    
    if P.IsEmpty():
        PP = PartialLevelOneTree()
        PP.tree = deepcopy(P)
        PP.node.MakeEntry([0])
        return [PP]
    else:
        

        PP = PartialLevelOneTree()
        PP.tree = deepcopy(P)
        PP.node.MakeEntry([-1])
        
        t = [PP]
        
        for ee in P.Enumerate():
            
            Q = PartialLevelOneTree()
            Q.tree = PP.tree
            
            f = SingleNode()
            k = ee.number_of_children
            f.MakeEntry(ee.Enumerate() + [k])
            
            Q.node = f
            
            t.append(Q)
        
        return t

def EnumerateNodesOfPartialLevelOneTree(P):    # makes a list of the nodes of partial level-1 trees whose component is P
    
    if P.IsEmpty():
        return [-1]
    
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
    
    def __init__(self):
        
        LevelOneNode.__init__(self)
        self.image = []
        
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
        
        if not self.IsEmpty():
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
        LevelOneTree.__init__(self)
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
    
    def ContainsElement (self, s, y):   #is s NONEMPTY AND a member of T and y is the image of s? (by default, emptyset is not in any tree) 

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
    
    def AddNodeBelow (self,s, y):  #add a node below s in the domain with value y, returns the new node in the tree
        
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
    


class LevelTwoTree(AttrLevelOneTree):
    'a level-2 tree'

    def __init__(self):
        
        AttrLevelOneTree.__init__(self)
        self.image = PartialLevelOneTree()
        cardinality = 1
        
    def Input(self,d):
        
        self.domain.Input()
        
        #link the nodes according to self.domain
        #request completions and hanging nodes...
        
    
P = DoubleTree()
P.Input(2)
