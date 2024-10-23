#ifndef UNORDERED_MAP_HPP
#define UNORDERED_MAP_HPP

template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class my_unordered_map {
public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = std::pair<const Key, T>;
	using size_type = std::size_t;
	using hasher = Hash;
	using key_equal = KeyEqual;
	using reference = value_type&;
	using const_reference = const value_type&;
	using r_reference = value_type&&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
private:
	using container = std::vector<std::forward_list<value_type>>;
	using container_pointer = container*;
	using obj_ptr = typename std::forward_list<value_type>::const_iterator;

	class base_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
		friend my_unordered_map<key_type, mapped_type, hasher, key_equal>;
	public:
		bool operator== (const base_iterator& other) {return ptr == other.ptr;};
		bool operator!= (const base_iterator& other) {return !(*this == other);};
	protected:
		explicit base_iterator (obj_ptr _ptr, container_pointer cont, size_type idx) : ptr{_ptr}, cp{cont}, bucket_index{idx} {}

		obj_ptr	ptr;
		container_pointer cp;
		size_type bucket_index;

		// helpers
		obj_ptr __get_next_bucket_begin(size_type& idx) const;
		obj_ptr __empty() const;
	};

	obj_ptr __find_first_elem (size_type& idx) const;
	obj_ptr __find_last_elem (size_type& idx) const;
public:
	class const_iterator : public base_iterator {
		friend my_unordered_map<key_type, mapped_type, hasher, key_equal>;
	public:
		const_iterator () : base_iterator(obj_ptr(), nullptr, 0) {}
		const_iterator (const const_iterator& other) : base_iterator(other.ptr, other.cp, other.bucket_index) {}
		const_iterator (const_iterator&& other) : base_iterator(other.ptr, other.cp, other.bucket_index) { other.ptr = obj_ptr(); other.cp = nullptr; other.bucket_index = 0;}
	protected:
		explicit const_iterator (obj_ptr _ptr, container_pointer cont, size_type idx) : base_iterator(_ptr, cont, idx) {}
	public:
		const const_iterator& operator= (const base_iterator& other);
		const const_iterator& operator= (base_iterator&& other);
		const const_iterator& operator++ ();
		const const_iterator operator++ (int);
		const_reference operator* () const;
		const_pointer operator-> () const;
	};

	class iterator : public const_iterator {
		friend my_unordered_map<key_type, mapped_type, hasher, key_equal>;
	public:
		iterator () : const_iterator(obj_ptr(), nullptr, 0) {}
		iterator (const iterator& other) : const_iterator(other.ptr, other.cp, other.bucket_index) {}
		iterator (iterator&& other) : const_iterator(other.ptr, other.cp, other.bucket_index) {other.ptr = obj_ptr(); other.cp = nullptr; other.bucket_index = 0;}
	protected:
		explicit iterator (obj_ptr _ptr, container_pointer cont, size_type idx) : const_iterator(_ptr, cont, idx) {}
	public:
		iterator& operator++ ();
		iterator operator++ (int);
		reference operator* () const;
		pointer operator-> () const;
	};
public:
	iterator begin();
	iterator end();
	const_iterator cbegin();
	const_iterator cend();
public:
	my_unordered_map() : C(7, std::forward_list<value_type>()) {}
	my_unordered_map(const my_unordered_map& other) : C{other} {}
	my_unordered_map(my_unordered_map&& other) : C{std::move(other)} {}
	my_unordered_map(const std::initializer_list<value_type>& il);
	~my_unordered_map() = default;
public:
	void clear () noexcept { C.clear(); }
	std::pair<iterator, bool> insert(const value_type& value);
	std::pair<iterator, bool> insert(value_type&& value);
	mapped_type& operator[] (const key_type& key);
	const mapped_type& operator[] (const key_type& key) const;
	size_type count(size_type idx) const;
	size_type size () const;
private:
	container C;
	hasher	__hasher;
	size_type __size;

	size_type __get_index(key_type key) const;
	void __size_fix();
	void __rehash();
	size_type __get_next_size(size_type size) const;
};

#endif // UNORDERED_MAP_HPP