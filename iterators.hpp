#ifndef ITERATORS_HPP
#define ITERATORS_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::obj_ptr
my_unordered_map<Key, T, Hash, KeyEqual>::base_iterator::__empty () const {
	return obj_ptr();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::obj_ptr
my_unordered_map<Key, T, Hash, KeyEqual>::base_iterator::__get_next_bucket_begin (size_type& idx) const {
	container_pointer C = this->cp;
	for (int i = idx + 1; i < C->size(); ++i) {
		if (!(*C)[i].empty()) {
			idx = i;
			return (*C)[i].begin();
		}
	}
	return (*C).back().end();
}


template <typename Key, typename T, typename Hash, typename KeyEqual>
const typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator&
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator= (const base_iterator& other) {
	this->ptr = other.ptr;
	this->cp = other.cp;
	return *this;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
const typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator&
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator= (base_iterator&& other) {
	this->ptr = other.ptr;
	this->cp = other.cp;
	other.ptr = nullptr;
	other.cp = nullptr;
	return *this;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
const typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator&
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator++ () {
	if (this->ptr == this->__empty()) return *this;

	container_pointer tmp = this->cp;
	++(this->ptr);
	if (this->ptr == (*tmp)[this->bucket_index].end())
		this->ptr = this->__get_next_bucket_begin(this->bucket_index);
	return *this;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
const typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator++ (int) {
	const_iterator tmp = *this;
	++(*this);
	return tmp;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::const_reference
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator* () const {
	return *(this->ptr);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::const_pointer
my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator::operator-> () const {
	return this->ptr.operator->();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator
my_unordered_map<Key, T, Hash, KeyEqual>::iterator::operator++ (int) {
	const_iterator::operator++(0);
	return (*this);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator&
my_unordered_map<Key, T, Hash, KeyEqual>::iterator::operator++ () {
	const_iterator::operator++();
	return (*this);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::reference
my_unordered_map<Key, T, Hash, KeyEqual>::iterator::operator* () const {
	return const_cast<reference>(static_cast<const const_iterator&>(*this).operator*());
	// return const_cast<my_unordered_map<Key, T, Hash, KeyEqual>::reference>(const_iterator::operator*());
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::pointer
my_unordered_map<Key, T, Hash, KeyEqual>::iterator::operator-> () const {
	return const_cast<pointer>(const_iterator::operator->());
}

#endif // ITERATORS_HPP