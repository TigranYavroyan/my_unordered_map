#ifndef CTORS_HPP
#define CTORS_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
my_unordered_map<Key, T, Hash, KeyEqual>::my_unordered_map(const std::initializer_list<value_type>& il) {
	C.resize(__get_next_size(il.size()));
	for (const auto& pair : il) {
		insert(pair);
	}
}

#endif // CTORS_HPP