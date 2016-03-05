#ifndef FC_DENDROGRAM_HPP
#define FC_DENDROGRAM_HPP

#include <vector>
#include <iterator>
#include <iostream>

//------------------------------------------------------------------------------
// MERGE CONTAINER
//------------------------------------------------------------------------------
template <typename SignedIntType>
class Merge
{
public:
  typedef SignedIntType sint_t;
  typedef std::vector<sint_t> container;
  
  class row : std::iterator<random_access_iterator_tag, sint_t>
  {
    friend class Merge<sint_t>;
    private:
      unsigned n_;
      iterator itr_;
      
    public:
      sint_t& first() { return *itr_; }
      sint_t& second() { return *(itr_ + (n_-1); }
      reference operator* () { return ptr->val; }

      row& operator++() { itr_++; return *this; }
      row operator++(int) { row r = *this; ++*this; return r; }
      
      row& operator--() { itr_--; return *this; }
      row operator--(int) { row r = *this; --*this; return r; }

      bool operator==(const row& r) const { return itr_ == r.itr_; }
      bool operator!=(const row& r) const { return itr_ != r.itr_; }
      
      bool operator<(const row& r) const { return itr_ < r.itr_; }
      bool operator<=(const row& r) const { return itr_ <= r.itr_; }
      bool operator>(const row& r) const { return itr_ > r.itr_; }
      bool operator>=(const row& r) const { return itr_ >= r.itr_; }
  };

private:
  unsigned  n_;
  container data_;

public:
  Merge() : n_(0) { }
  
  Merge(unsigned n = 0) : n_(n)
  {
    if(n_ != 0) { data_ = container((n_ - 1) * 2, 0); }
  }
  
  Merge(const Merge<sint_t>& m) : n_(m.n_), data_(m.data_) { }
  
  Merge<sint_t>& operator=(const Merge<sint_t>& m)
  {
    if(this == &m) { return *this; }
    n_ = m.n_;
    data_.reserve((n_-1)*2);
    data_.assign(m.data_.begin(), m_data.end());
    return *this;
  }
  
  ~Merge() { }
  
  
  #if __cplusplus >= 201103L
  inline sint_t* data() noexcept { return data_.data(); }
  inline const sint_t* data() const noexcept { return data_.data(); }
  #else
  inline sint_t* data() { return &data_[0]; }
  inline const sint_t* data() const { return &data_[0]; }
  #endif
  
};

//------------------------------------------------------------------------------
// DENDROGRAM CONTAINER
//------------------------------------------------------------------------------
class Dendrogram
{
public:
  #if __cplusplus < 201103L
  class Height : public std::vector<double>
  {
  public:
    double* data() { return &(this->front()); }
  };
  class Order : public std::vector<double>
  {
  public:
    int* data() { return &(this->front()); }
  }
  #else
  typedef std::vector<double> Height;
  typedef std::vector<int> Order;
  #endif

private:
  unsigned int  n_;        //number of nodes
  Merge<int>    merge_;    //(N-1)x2 matrix
  Height        height_;   //N-1 vector
  Order         order_;    //N vector
  
public:
  Dendrogram() : n_(0) { }
    
  Dendrogram(const MDendrogram& m)
    : n_(0), merge_(m.merge_), height_(m.height_), order_(m.order_) { }
  
  Dendrogram& operator=(const Dendrogram& m)
  {
    if(this == &m) { return *this; }
    if(N_ != m.N_)
    {
      this->free();
      this->init(m.N_);
    }
    for(IntType i = 0; i < N_; i++)
    {
      order_[i] = m.order_[i];
      if(i < (unsigned int)N_-1)
        height_[i] = m.height_[i];
    }
    for(unsigned int i = 0; i < ((unsigned int)N_-1)*2; i++)
    {
      merge_[i] = m.merge_[i];
    }
    return *this;
  }

  Dendrogram(unsigned int n) : n_(n) { init(n); }
  
  ~Merge() { }
  
  void clear()
  {
    n_ = 0;
    merge_.clear();
    height_.clear();
    order_.clear();
  }
  
  IntType get_n() const { return N_; }
  IntType  size() const { return N_; }
  
  IntType*    merge() { return merge_;  }
  FloatType* height() { return height_; }
  IntType*    order() { return order_;  }
  
  const long* merge() const { return merge_;  }
  const FloatType* height() const { return height_; }
  const IntType*    order() const { return order_;  }
};

#endif //FC_DENDROGRAM_HPP
