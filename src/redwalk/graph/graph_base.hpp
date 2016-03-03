//
// Created by peter on 1/23/16.
//

#ifndef REDWALK_GRAPH_HPP
#define REDWALK_GRAPH_HPP

//#include <iterator>

////////////////////////////////////////////////////////////////////////////////
// NEIGHBORHOOD LIST
////////////////////////////////////////////////////////////////////////////////
namespace redwalk
{

template <typename vertex_id_t>
class NeighborhoodList
{
public:
  typedef vertex_id_t    vid_t;
  typedef vid_t          idx_t;
  typedef vid_t*         iterator;
  typedef const iterator const_iterator;

private:
  iterator beg_ = nullptr;
  iterator end_ = nullptr;

public:
  NeighborhoodList(iterator beg, iterator end) : beg_(beg), end_(end) { }

  const_iterator begin()  const { return beg_; }
  const_iterator end()    const { return end_; }
  const_iterator cbegin() const { return beg_; }
  const_iterator cend()   const { return end_; }

  inline idx_t size()   const { return end_ - beg_; }
  inline idx_t degree() const { return end_ - beg_; }

  inline vid_t operator[](idx_t i) const { return *(beg_ + i); }
  inline vid_t operator()(idx_t i) const { return *(beg_ + i); }
  inline vid_t         at(idx_t i) const { return *(beg_ + i); }
}; //class NeighborList

////////////////////////////////////////////////////////////////////////////////
// GRAPH
////////////////////////////////////////////////////////////////////////////////
template <typename vertex_id_t>
class graph_base
{
public:
  typedef vertex_id_t vid_t;
  typedef vid_t       idx_t;
  typedef NeighborhoodList<vid_t> NeighborList;

private:
  idx_t nv_;
  idx_t ne_;

protected:
  void set_nv(idx_t nv) { nv_ = nv; }
  void set_ne(idx_t ne) { ne_ = ne; }

public:
  explicit graph_base(idx_t nv = 0, idx_t ne = 0) : nv_(nv), ne_(ne) { }
  virtual ~graph_base() { }

  virtual inline idx_t vcount() const { return nv_; }
  virtual inline idx_t ecount() const { return ne_; }

  virtual NeighborList operator[](vid_t) const = 0;
  virtual idx_t degree(vid_t) const = 0;
};  //class graph_base

} //namespace redwalk

#endif //REDWALK_GRAPH_H
