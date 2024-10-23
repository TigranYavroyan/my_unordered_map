#ifndef INSERTION_HPP
#define INSERTION_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
std::pair<typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator, bool>
my_unordered_map<Key, T, Hash, KeyEqual>::insert (const value_type& value) {
	size_type index = __get_index(value.first);
	auto it = std::find_if(C[index].begin(), C[index].end(),[&value](const value_type& to_find){return to_find.first == value.first;});
	if (it == C[index].end())
	{
		C[index].push_front(value);
		++__size;
		__size_fix();
		return {iterator(C[index].begin(), &C, index), true};
	}
	return {iterator(it, &C, index), false};
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
std::pair<typename my_unordered_map<Key, T, Hash, KeyEqual>::iterator, bool>
my_unordered_map<Key, T, Hash, KeyEqual>::insert (value_type&& value) {
	size_type index = __get_index(value.first);
	auto it = std::find_if(C[index].begin(), C[index].end(),[&value](const value_type& to_find){return to_find.first == value.first;});
	if (it == C[index].end())
	{
		C[index].push_front(std::move(value));
		++__size;
		__size_fix();
		return {iterator(C[index].begin(), &C, index), true};
	}
	return {iterator(it, &C, index), false};
}


#endif // INSERTION_HPP