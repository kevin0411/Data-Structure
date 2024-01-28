#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    this->pic = png;
    this->start = start;
    this->tolerance = tolerance;
    this->functions = fns;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return Iterator(*this);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }


  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    this->pic = PNG();
    this->start = Point();
    this->current = Point();
    this->func = TraversalFunctions();
    this->work_list_ = std::deque<Point>();
    this->visit = std::vector<std::vector<bool>>();
    this->tolerance = 0;
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator(ImageTraversal it) {
    /** @todo [Part 1] */
    this->pic = it.pic;
    this->start = it.start;
    this->current = it.start;
    this->func = it.functions;
    this->tolerance = it.tolerance;
    visit.resize(pic.width());
    for(int i=0;i<(int)(visit.size());i++){
      visit[i].resize(pic.height());
      for(int j=0;j<(int)pic.height();j++){
        visit[i][j] = false;
      }
    }
    visit[start.x][start.y]= true;
    Point right = Point(start.x + 1, start.y);
    Point down = Point(start.x, start.y + 1);
    Point left = Point(start.x - 1, start.y);
    Point up = Point(start.x, start.y - 1);
    if(right.x>=0 && right.x<pic.width() && right.y>=0 && right.y < pic.height() && visit[right.x][right.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(right.x, right.y))<tolerance){
      func.add(work_list_, right);
    }
    if(down.x>=0 && down.x<pic.width() && down.y>=0 && down.y < pic.height() && visit[down.x][down.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(down.x, down.y))<tolerance){
      func.add(work_list_, down);
    }
    if(left.x>=0 && left.x<pic.width() && left.y>=0 && left.y < pic.height() && visit[left.x][left.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(left.x, left.y))<tolerance){
      func.add(work_list_, left);
    }
    if(up.x>=0 && up.x<pic.width() && up.y>=0 && up.y < pic.height() && visit[up.x][up.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(up.x, up.y))<tolerance){
      func.add(work_list_, up);
    }
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    if(work_list_.empty()){
        this->pic = PNG();
        this->start = Point();
        this->current = Point();
        this->func = TraversalFunctions();
        this->work_list_ = std::deque<Point>();
        this->visit = std::vector<std::vector<bool>>();
        this->tolerance = 0;
        return *this;
    }
    Point visited = func.peek(work_list_);
    func.pop(work_list_);
    while(visit[visited.x][visited.y]==true){
      if(work_list_.empty()){
        this->pic = PNG();
        this->start = Point();
        this->current = Point();
        this->func = TraversalFunctions();
        this->work_list_ = std::deque<Point>();
        this->visit = std::vector<std::vector<bool>>();
        this->tolerance = 0;
        return *this;
      }
      visited = func.peek(work_list_);
      func.pop(work_list_);
    }
    visit[visited.x][visited.y]= true;
    current = visited;
    Point right = Point(visited.x + 1, visited.y);
    Point down = Point(visited.x, visited.y + 1);
    Point left = Point(visited.x - 1, visited.y);
    Point up = Point(visited.x, visited.y - 1);
    if(right.x>=0 && right.x<pic.width() && right.y>=0 && right.y < pic.height() && visit[right.x][right.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(right.x, right.y))<tolerance){
      func.add(work_list_, right);
    }
    if(down.x>=0 && down.x<pic.width() && down.y>=0 && down.y < pic.height() && visit[down.x][down.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(down.x, down.y))<tolerance){
      func.add(work_list_, down);
    }
    if(left.x>=0 && left.x<pic.width() && left.y>=0 && left.y < pic.height() && visit[left.x][left.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(left.x, left.y))<tolerance){
      func.add(work_list_, left);
    }
    if(up.x>=0 && up.x<pic.width() && up.y>=0 && up.y < pic.height() && visit[up.x][up.y]==false && calculateDelta(pic.getPixel(start.x, start.y), pic.getPixel(up.x, up.y))<tolerance){
      func.add(work_list_, up);
    }
    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return !(this->pic == other.pic && this->start == other.start && this->work_list_ == other.work_list_ && this->visit == other.visit && this->current == other.current);
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}