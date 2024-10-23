#ifndef COUNT_HPP
#define COUNT_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::size_type
my_unordered_map<Key, T, Hash, KeyEqual>::count (size_type idx) const {
	const std::forward_list<value_type>& curr = C.at(idx);
	return std::distance(curr.begin(), curr.end());
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::size_type
my_unordered_map<Key, T, Hash, KeyEqual>::size () const {
	return C.size();
}

#endif // COUNT_HPP