/* Your code here! */
#include "dsets.h"

    /**
     * Creates n unconnected root nodes at the end of the vector.
     * @param num The number of nodes to create
     */
void DisjointSets::addelements(int num){
    for(int i=0;i<num;i++)
        uptree.push_back(-1);
}

    /**
     * This function should compress paths and works as described in lecture.
     * @return the index of the root of the up-tree in which the parameter
     *  element resides.
     */
int DisjointSets::find(int elem){
    if((int)uptree.size()<=elem)return -1;
    int it = elem;
    while(uptree[it]>=0){
        it = uptree[it];
    }
    return it;
}

    /**
     * This function should be implemented as union-by-size. That is, when you
     * setunion two disjoint sets, the smaller (in terms of number of nodes)
     * should point at the larger. This function works as described in lecture,
     * except that you should not assume that the arguments to setunion are
     * roots of existing uptrees.
     *
     * Your setunion function SHOULD find the roots of its arguments before
     * combining the trees. If the two sets are the same size, make the tree
     * containing the second argument point to the tree containing the first.
     * (Note that normally we could break this tie arbitrarily, but in this case
     * we want to control things for grading.)
     *
     * @param a Index of the first element to union
     * @param b Index of the second element to union
     */
void DisjointSets::setunion(int a, int b){
    int root_A = find(a);
    int root_B = find(b);
    if(root_A!=root_B){
        if(uptree[root_A] > uptree[root_B]){
            uptree[root_B] += uptree[root_A];
            uptree[root_A] = root_B;
        }
        else{
            uptree[root_A] += uptree[root_B];
            uptree[root_B] = root_A;
        }
    }
    return;
}
    
    /**
     * This function should return the number of nodes in the up-tree containing 
     * the element.
     * @return number of nodes in the up-tree containing the element
     */
int DisjointSets::size(int elem){
    return uptree[find(elem)]*-1;
}

