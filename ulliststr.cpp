#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>

////////////
//Valgrind errors
///////////

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  Item* temp = head_;
  int count = 0;
  while(true) {
    if(count + temp->last - temp->first > loc) {
      return &temp->val[temp->first+loc-count];
    }
    count += temp->last - temp->first;
    if(temp->next == NULL) {
      return NULL;
    }
    temp = temp->next;
  }
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val) {
  if(head_ == NULL) {
    head_ = new Item();
    tail_ = head_;
  }
  if(tail_->last < ARRSIZE-1) {
    tail_->val[tail_->last] = val;
    tail_->last ++;
  }
  else {
    tail_->next = new Item();
    Item* temp = tail_;
    tail_ = tail_->next;
    tail_->prev = temp;
    tail_->val[0] = val;
    tail_->first = 0;
    tail_->last = 1;
  }
  size_++;
}

void ULListStr::pop_back() {
  if(size_ > 0) {
    tail_->last --;
    size_ --;
    if(tail_->last < 1) {
      if(size_ > 0) {
        Item* temp = tail_;
        tail_ = tail_->prev;
        delete temp;
      }
      else {
        delete tail_;
        head_ = tail_ = NULL;
      }
    }
  }
}

void ULListStr::pop_front() {
  if(size_ > 0) {
    head_->first ++;
    size_ --;
    if(head_->first > ARRSIZE-2) {
      if(size_ > 0) {
        Item* temp = head_;
        head_ = head_->next;
        delete temp;
      }
      else {
        delete head_;
        tail_ = head_ = NULL;
      }
    }
  }
}

std::string const & ULListStr::back() const {
  return tail_->val[tail_->last-1];
}

void ULListStr::push_front(const std::string& val) {
  if(head_ == NULL) {
    head_ = new Item();
    tail_ = head_;
    head_->val[ARRSIZE-1] = val;
    head_->first = ARRSIZE-1;
    head_->last = ARRSIZE;
  }
  else {
    if(head_->first > 0) {
      head_->val[head_->first -1] = val;
      head_->first --;
    }
    else {
      head_->prev = new Item();
      Item* temp = head_;
      head_ = head_->prev;
      head_->next = temp;
      head_->val[ARRSIZE-1] = val;
      head_->first = ARRSIZE-1;
      head_->last = ARRSIZE;
    }
  }
  size_++;
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}