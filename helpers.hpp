#ifndef HELPERS_HPP
#define HELPERS_HPP

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::size_type
my_unordered_map<Key, T, Hash, KeyEqual>::__get_index (key_type key) const {
	size_type res = __hasher(key);
	return res % C.size();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void
my_unordered_map<Key, T, Hash, KeyEqual>::__size_fix() { // add size_fixing when size is 85% of C.size()
	double tmp = static_cast<double>(__size / C.size()) * 100;
	const double max_size = 85.0;
	if (tmp > max_size)
		__rehash();
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
void
my_unordered_map<Key, T, Hash, KeyEqual>::__rehash() {
	size_type counter = __size;
	container new_C(__get_next_size(C.size()), std::forward_list<value_type>());
	iterator it = begin();
	int idx;

	while (counter--) {
		idx = __hasher(it->first) % new_C.size();
		new_C[idx].push_front(*it);
		++it;
	}
	C = std::move(new_C);
}

template <typename Key, typename T, typename Hash, typename KeyEqual>
typename my_unordered_map<Key, T, Hash, KeyEqual>::size_type
my_unordered_map<Key, T, Hash, KeyEqual>::__get_next_size (size_type size) const {
	auto is_prime = [](size_type size)
	{
		if (size <= 1) return false;
		if (size == 2 || size == 3) return true;
		if (size % 2 == 0 || size % 3 == 0) return false;

		for (int i = 5; i < size / 2; i += 6) {
			if (size % i == 0 || size % (i + 2) == 0) {
				return false;
			}
		}
		return true;
	};

	size_type res = size + 1;
	while(!is_prime(res))
		++res;
	
	if (res - size <= 5)
	{
		while(!is_prime(res))
			++res;
	}

	return res;
}

#endif // HELPERS_HPP