import sys
# In this file, the Phylogenetic tree has been implemented. The preorder traversal was used to associate the spicies name with
# offspring number, then the postorder traversal was used to print out the names of the dependents and the average number of offsprings
# programmed by; Chaolun Wang

#part 1
class Tree:
    
    #node for tree 
    class Node:
        def __init__(self, name= None, ancestor = None, left=None, right=None, length = None, off=0):
            
            self.name = name             #spicies name 
            self.ancestor = ancestor     # the node represent ancestor
            self.left = left             # left child 
            self.right = right           #right child
            self.length = length         #store length of specific node to its parent
            self.off=off                 #store the number of offsprings

        #getters for memeber datas
        def getName(self):         #get name of the species
            return self.name
            
        def getAncestor(self):     #get to the node of ancestor
            return self.ancestor  
            
        def getLen(self):          #get the length to its ancestor
            return self.length         
  
        def getLeft(self):         #get the left child
            return self.left
            
        def getRight(self):        #get the right child
            return self.right  
            
        def getOff(self):          #get off spring numbers
            return self.off      
            
        #setters for member datas
        def setName(self, name):           #set the species name
            self.name = name
            
        def setAncestor(self, ancestor):   #set the ancestor
            self.ancestor =ancestor
        
        def setLen(self, lenth):           #set the length towards the ancestor
            self.length = lenth

        def setLeft(self,left):            #set the left child
            self.left =left
            
        def setRight(self, right):         #set the right child
            self.right = right
            
        def setOff(self,offspring):        #set the offspring number
            self.off = offspring
          
    #initialize tree as an empty node             
    def __init__(self):             
        self.root = Tree.Node()


        
def constructTree(newick):

    i = 0    
    p = Tree() 
    tree = None  

    while newick[i] != ';':  #non-recursive algorithm was used referred to : https://people.sc.fsu.edu/pbeerli/isc5317-notes/pdfs/09trees.pdf
        if newick[i] == '(':
            i=i+1
            q = Tree()
            p.root.setLeft(q.root)
            q.root.setAncestor(p.root)
            if i == 1:
                tree = p
            p = q
        elif newick[i] == ',':
            q = Tree()
            if  p.root.getAncestor().getLeft()==p.root:    #test if p is a left child of the parent
                p.root = p.root.getAncestor()
                p.root.setRight(q.root)
            else:
                p.root = p.root.getAncestor()
                p.root.setAncestor(q.root)
            
            q.root.setAncestor(p.root)
            p = q
            i=i+1
        elif newick[i] == ')':
            p.root = p.root.getAncestor()
            i=i+1
        else:
            string = "";
            while newick[i] != ':':
                string = string+newick[i]
                i = i + 1
            i = i + 1
            length = []
            while newick[i] != ',' and newick[i] != ')':
                 length.append(newick[i])
                 i = i + 1
            if string != "":
                p.root.setName(string);
                p.root.setLen(length)
    return tree 

#part 2 prorder traversal

def preorder(node, offspring): 
    if node == None:
        return

    if node.getName() != None:
        node.setOff(offspring[node.getName()]);    #associate the number of offspring to the tree when doing the preorder traversal
        
    preorder(node.getLeft(), offspring)
    preorder(node.getRight(), offspring)

#part 3 postorder traversal

def postorder(node):
    if node == None:
        return
    postorder(node.getLeft())
    postorder(node.getRight())
    if node.getName() == None:               #recursively update the ancestor's name and average offspring and print out. Postorder guarantees the order of updation and the printout
        node.setName(node.getLeft().getName()+"_"+node.getRight().getName())
        node.setOff((node.getRight().getOff()+node.getLeft().getOff())*0.5)
        print node.getName(), node.getOff()  #print out the name and offspring number
    
#main function

if __name__ == "__main__":
    #offspring dictionary    
    offspring = {None: None}
    offspring['Chimp'] = 1
    offspring['Cow'] = 1.5
    offspring['Bird'] = 5
    offspring['Toad'] = 400
    offspring['SeaBass'] = 200000
    
    #pass the parameters from the main function 
    if len(sys.argv) < 2:
        print "Error: Input file required"
        exit()

    #input & build tree
    inputfile = open(sys.argv[1] )
    newick = inputfile.readline()
    tree = constructTree(newick) 
    
    root = tree.root
    #preorder traversal associat the tree with name-offspring number pair
    preorder(root,offspring) 
    
    #postorder traversal
    postorder(root) 
