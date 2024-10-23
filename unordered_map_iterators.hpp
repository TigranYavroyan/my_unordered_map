#ifndef UNORDERED_MAP_ITERATORS_HPP
#define UNORDERED_MAP_ITERATORS_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::obj_ptr
my_unordered_map<Key, T, Hash, KeyEqual>::__find_first_elem (size_type& idx) const {
	idx = 0;
	for (int i = 0; i < C.size(); ++i) {
		if (!C[i].empty()) {
			idx = i;
			return C[i].begin();
		}
	}
	return C.front().begin();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::obj_ptr
my_unordered_map<Key, T, Hash, KeyEqual>::__find_last_elem (size_type& idx) const {
	obj_ptr	end = C.back().end();
	idx = C.size() - 1;
	for (int i = 0; i < C.size(); ++i) {
		if (!C[i].empty()) {
			idx = i;
			end = C[i].end();
		}
	}
	return C.back().end();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator
my_unordered_map<Key, T, Hash, KeyEqual>::begin () {
	size_type idx;
	obj_ptr tmp = __find_first_elem(idx);
	return iterator(tmp, &C, idx);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator
my_unordered_map<Key, T, Hash, KeyEqual>::cbegin () {
	size_type idx;
	obj_ptr tmp = __find_first_elem(idx);
	return const_iterator(tmp, &C, idx);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator
my_unordered_map<Key, T, Hash, KeyEqual>::end () {
	size_type idx;
	obj_ptr tmp = __find_last_elem(idx);
	return iterator(tmp, &C, idx);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::const_iterator
my_unordered_map<Key, T, Hash, KeyEqual>::cend () {
	size_type idx;
	obj_ptr tmp = __find_last_elem(idx);
	return const_iterator(tmp, &C, idx);
}


#endif // UNORDERED_MAP_ITERATORS_HPP