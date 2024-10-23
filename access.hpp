#ifndef ACCESS_HPP
#define ACCESS_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
const typename my_unordered_map<Key, T, Hash, KeyEqual>::mapped_type&
my_unordered_map<Key, T, Hash, KeyEqual>::operator[] (const key_type& key) const {
	size_type index = __get_index(key);
	auto it = std::find_if(C[index].begin(), C[index].end(),[&key](const value_type& to_find){return to_find.first == key;});
	if (it == C[index].end())
	{
		C[index].push_front({key, mapped_type()});
		it = C[index].begin();
	}
	return it->second;
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::mapped_type&
my_unordered_map<Key, T, Hash, KeyEqual>::operator[] (const key_type& key) {
	size_type index = __get_index(key);
	auto it = std::find_if(C[index].begin(), C[index].end(),[&key](const value_type& to_find){return to_find.first == key;});
	if (it == C[index].end())
	{
		C[index].push_front({key, mapped_type()});
		it = C[index].begin();
	}
	return it->second;
}

#endif // ACCESS_HPP