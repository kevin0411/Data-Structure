/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]<second[curDim])return true;
    if(first[curDim]==second[curDim])return first<second;
    return false;
}

template <int Dim>
double dist(const Point<Dim>& a, const Point<Dim>& b){
  double distance =0;
  for(int i=0;i<Dim;i++){
    distance += (a[i]-b[i])*(a[i]-b[i]);
  }
  return distance;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double best_dist = dist(currentBest, target);
    double pot_dist = dist(potential, target);
    if(pot_dist<best_dist)return true;
    if(pot_dist==best_dist)return potential<currentBest;
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> copy = vector<Point<Dim>>(newPoints);
    root = buildTree(copy,0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.size()==0)return NULL;
    int r = ((int)newPoints.size()-1)/2;
    auto cmp = [=](Point<Dim> lhs, Point<Dim> rhs){
      return smallerDimVal(lhs,rhs,curDim);
    };
    curDim++;
    curDim %= Dim;
    select(newPoints.begin(),newPoints.end(),newPoints.begin()+r, cmp);
    KDTreeNode* root = new KDTreeNode(newPoints[r]);
    vector<Point<Dim>> left_vec = vector<Point<Dim>>(newPoints.begin(),newPoints.begin()+r);
    root->left = buildTree(left_vec,curDim);
    vector<Point<Dim>> right_vec = vector<Point<Dim>>(newPoints.begin()+r+1,newPoints.end());
    root->right = buildTree(right_vec,curDim);
    return root;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = new KDTreeNode(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  root = rhs.root;
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete root;
  size = 0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* node, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(node->left==NULL && node->right==NULL)return node->point;
    Point<Dim> bestNode = node->point;
    Point<Dim> potential = bestNode;
    bool go_left = smallerDimVal(query, bestNode, curDim);
    if(go_left && node->left!=NULL){
      potential = findNearestNeighbor(query, node->left, (curDim+1)%Dim);
    }
    if(!go_left && node->right!=NULL){
      potential = findNearestNeighbor(query, node->right, (curDim+1)%Dim);
    }
    if(shouldReplace(query, bestNode, potential)){
      bestNode = potential;
    }

    double potential_area = dist(query, potential);
    double current_r = query[curDim]-node->point[curDim];
    double current_area = current_r * current_r;
  
    if(current_area <= potential_area){
      if(!go_left && node->left!=NULL){
        potential = findNearestNeighbor(query, node->left, (curDim+1)%Dim);
        if(shouldReplace(query, bestNode, potential)){
          bestNode = potential;
        }
      }
      if(go_left && node->right!=NULL){
        potential = findNearestNeighbor(query, node->right, (curDim+1)%Dim);
        if(shouldReplace(query, bestNode, potential)){
          bestNode = potential;
        }
      }
    }
    return bestNode;
}

template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter index, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */
    RandIter temp = index;
    std::iter_swap(temp, end);
    RandIter it = start;
    RandIter i = start;
    while(i!=end){
      if(!cmp(*end,*i)){
        std::iter_swap(it,i);
        it++;
      }
      i++;
    }
    std::iter_swap(end, it);
    return it;
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */
    
    if(start==end-1)return;
    int k_dist = std::distance(start,k);
    RandIter temp = start + 1;
    temp = partition(start, end-1, temp, cmp);
    int temp_dist = std::distance(start,temp);

    if(temp_dist==k_dist)return;
    else if(k_dist<temp_dist){
      select(start, temp, start+k_dist, cmp);
    }
    else{
      select(++temp, end, start+k_dist, cmp);
    }
}
