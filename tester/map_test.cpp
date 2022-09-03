#include <iostream>
#include <string>

#ifdef _CONTAINER_TESTER_STD
namespace ft = std;
	# include <map>
#else
	# include "map.hpp"
#endif

typedef ft::pair<int, std::string> pair;

std::ostream &operator<<(std::ostream &out, const pair &p) {
	out << "(" << p.first << "; " << p.second << ")";
	return out;
} 

template <typename Iter>
void
print_map_content(Iter first, Iter last) {
	std::cout << " content  : [";
	for (; first != last; ++first) {
		std::cout << " ("<< (*first).first << "; " << (*first).second << ")";
	}
	std::cout << " ]" << std::endl;
}

template <typename Key, typename Val>
void
print_map(const ft::map<Key, Val>& map) {
	std::cout << " empty : " << map.empty() << std::endl; 
	std::cout << " size  : " << map.size() << std::endl;
	std::cout << " max_size : " << map.max_size() << std::endl;
	print_map_content(map.begin(), map.end());
}

void
map_test(void) {

	std::cout << "---------- map:" << std::endl;

	pair::first_type key1[] = { 1, 2, 3, 6, 5, 4, 4 };
	const pair::first_type size1 = sizeof(key1) / sizeof(key1[0]);
	pair::second_type val1[size1] = { "ichi", "ni", "san", "roku", "go", "yon", "shiranai" };
	pair p1[size1];
	for (size_t i = 0; i < size1; i++) {
		p1[i] = ft::make_pair(key1[i], val1[i]);
	}

	pair::first_type key2[] = { 21, 42, 84, 168, 336, 672 };
	const pair::first_type size2 = sizeof(key2) / sizeof(key2[0]);
	pair::second_type val2[size2] = { "nijuuichi", "yonjuuni", "hachijuuyon", "hyakurokujuuhachi", "sambyakusanjuuroku", "roppyakunanajuuni" };
	pair p2[size2];
	for (size_t i = 0; i < size2; i++) {
		p2[i] = ft::make_pair(key2[i], val2[i]);
	}
	pair::first_type exist_key = 336;
	pair::first_type nonexist_key = 1024;
	pair::second_type value = "machigatta";

	pair::first_type key3[] = { 21, 42, 84, 336, 672 };
	const pair::first_type size3 = sizeof(key3) / sizeof(key3[0]);
	pair::second_type val3[size3] = { "nijuuichi", "yonjuuni", "hachijuuyon", "sambyakusanjuuroku", "roppyakunanajuuni" };
	pair p3[size3];
	for (size_t i = 0; i < size3; i++) {
		p3[i] = ft::make_pair(key3[i], val3[i]);
	}
	pair missing3 = ft::make_pair(1024, "yon");

	pair::first_type key4[] = { 168, 1344, 2688 };
	const pair::first_type size4 = sizeof(key4) / sizeof(key4[0]);
	pair::second_type val4[size4] = { "hyakurokujuuhachi", "issensambyakuyonjuuyon", "nisenroppyakuhachijuuhachi" };
	pair p4[size4];
	for (size_t i = 0; i < size4; i++) {
		p4[i] = ft::make_pair(key4[i], val4[i]);
	}

	pair comp_a = ft::make_pair(21, "nijuuichi");
	pair comp_b = ft::make_pair(42, "yonjuuni");

	std::cout << " Constructors:" << std::endl;
	{
		std::cout << " constructor(default):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " constructor(first, last):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p1, p1 + size1);
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " copy constructor:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		ft::map<pair::first_type, pair::second_type> map2(map);
		print_map(map);
		std::cout << std::endl;
		print_map(map2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator=:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		ft::map<pair::first_type, pair::second_type> map2;
		map2 = map;
		print_map(map);
		std::cout << std::endl;
		print_map(map2);
		std::cout << std::endl;
	}

	std::cout << "----- Iterators:" << std::endl;
	{
		std::cout << " begin() -> end():" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map_content(map.begin(), map.end());
		std::cout << std::endl;
	}

	{
		std::cout << " begin() const -> end() const:" << std::endl;
		const ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map_content(map.begin(), map.end());
		std::cout << std::endl;
	}
	
	{
		std::cout << " rbegin() -> rend():" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map_content(map.rbegin(), map.rend());
		std::cout << std::endl;
	}

	{
		std::cout << " rbegin() const -> rend() const:" << std::endl;
		const ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map_content(map.rbegin(), map.rend());
		std::cout << std::endl;
	}

	std::cout << "----- Capacity:" << std::endl;
	{
		std::cout << " empty (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " size:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		std::cout << std::endl;
	}


	{
		std::cout << " max size:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		std::cout << std::endl;
	}

	std::cout << "----- Element access:" << std::endl;

	{
		std::cout << " operator[] (existing element):" << std::endl;
		
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		map[exist_key] = value;
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " operator[] (non-existing element):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		map[nonexist_key] = value;
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " at (existing val):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		map.at(exist_key) = value;
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " at (non-existing val):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		try {
			map.at(nonexist_key);
		} catch(const std::exception &e) {
			std::cout << "  exception: " << e.what() << std::endl;
		}
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}


	{
		std::cout << " at const (existing element):" << std::endl;
		const ft::map<pair::first_type, pair::second_type>	map(p2, p2 + size2);
		print_map(map);
		map.at(exist_key);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " at const (non-existing element):" << std::endl;
		const ft::map<pair::first_type, pair::second_type>	map(p2, p2 + size2);
		print_map(map);
		try {
			map.at(nonexist_key);
		} catch(const std::exception &e) {
			std::cout << "  exception:  " << e.what() << std::endl;
		}
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	std::cout << "----- Modifiers:" << std::endl;
	{
		std::cout << " insert(pair):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		print_map(map);
		map.insert(missing3);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " insert(hint, pair):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		print_map(map);
		map.insert(map.begin(), missing3);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " insert(first, last): " << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		print_map(map);
		map.insert(p4, p4 + size4);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(pos):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.begin();
		++it;
		++it;
		++it;
		map.erase(it);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		map.erase(exist_key);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(first, last):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.begin();
		ft::map<pair::first_type, pair::second_type>::iterator it2 = map.begin();
		++it;
		++it2;
		++it2;
		++it2;
		map.erase(it, it2);
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	{
		std::cout << " swap:" << std::endl;		
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		print_map(map);
		std::cout << std::endl;
		print_map(map2);
		map.swap(map2);
		std::cout << std::endl;
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
		print_map(map2);
		std::cout << std::endl;
	}

	{
		std::cout << " clear:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		map.clear();
		std::cout << std::endl;
		print_map(map);
		std::cout << std::endl;
	}

	std::cout << "----- Observers:" << std::endl;
	{
		std::cout << " key_comp (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		std::cout << "  cmp( " << comp_a.first << "," << comp_b.first << " )" << (map.key_comp()(comp_a.first, comp_b.first));
		std::cout << std::endl;
	}

	{
		std::cout << " key_comp (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		std::cout << "  cmp( " << comp_b.first << "," << comp_a.first << " )" << (map.key_comp()(comp_b.first, comp_a.first));
		std::cout << std::endl;
	}

	{
		std::cout << " value_comp (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		std::cout << "  cmp( " << comp_a << "," << comp_b << " )" << (map.value_comp()(comp_a, comp_b));
		std::cout << std::endl;
	}


	{
		std::cout << " value_comp (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map;
		std::cout << "  cmp( " << comp_a << "," << comp_b << " )" << (map.value_comp()(comp_b, comp_a));
		std::cout << std::endl;
	}

	std::cout << "----- Operations:" << std::endl;
	{
		std::cout << " find(existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.find(exist_key);
		std::cout << std::endl;
		print_map_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " find(non-existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator	it = map.find(nonexist_key);
		if (it != map.end()) {
			std::cout << std::endl;
			print_map_content(it, ++it);
		}
		std::cout << std::endl;
	}


	{
		std::cout << " count(existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		std::cout << std::endl;
		std::cout << " count(" << exist_key << "): " << map.count(exist_key) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " count(non-existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		std::cout << std::endl;
		std::cout << "  count(" << nonexist_key << "): " << map.count(nonexist_key) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.lower_bound(exist_key);
		std::cout << std::endl;
		print_map_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(non-existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.lower_bound(nonexist_key);
		if (it != map.end()) {
			std::cout << std::endl;
			print_map_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		std::cout << " upper_bound(existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.upper_bound(exist_key);
		std::cout << std::endl;
		print_map_content(it, ++it);
		std::cout << std::endl;
	}


	{
		std::cout << " upper_bound(non-existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::map<pair::first_type, pair::second_type>::iterator it = map.upper_bound(nonexist_key);
		if (it != map.end()) {
			std::cout << std::endl;
			print_map_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		typedef ft::map<pair::first_type, pair::second_type>::iterator iter;
	
		std::cout << " equal_range(existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::pair<iter, iter> it = map.equal_range(exist_key);
		std::cout << std::endl;
		print_map_content(it.first, it.second);
		std::cout << std::endl;
	}

	{
		typedef ft::map<pair::first_type, pair::second_type>::iterator iter;

		std::cout << " equal_range(non-existing key):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		print_map(map);
		ft::pair<iter, iter> it = map.equal_range(nonexist_key);
		std::cout << std::endl;
		print_map_content(it.first, it.second);
		std::cout << std::endl;
	}

	std::cout << "----- Non-member function overloads:" << std::endl;
	{
		std::cout << " operator== (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		std::cout << "  m == m: " << (map == map);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m1 == m2: " << (map == map2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		std::cout << "  m != m: " << (map != map);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m1 != m2: " << (map != map2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator< (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p2, p2 + size2);
		std::cout << "  m < m: " << (map < map);
		std::cout << std::endl;
	}

	{
		std::cout << " operator< (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m1 < m2: " << (map < map2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator<= (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m2 <= m1: " << (map2 <= map);
		std::cout << std::endl;
	}

	{
		std::cout << " operator<= (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m1 <= m2: " << (map <= map2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator> (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m2 > m1:  " << (map2 > map);
		std::cout << std::endl;
	}

	{
		std::cout << " operator> (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m1 > m2: " << (map > map2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator>= (true):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << "  m2 >= m1: " << (map2 >= map);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		std::cout << " m1 >= m2: " << (map >= map2);
		std::cout << std::endl;
	}

	{
		std::cout << " swap:" << std::endl;
		ft::map<pair::first_type, pair::second_type> map(p3, p3 + size3);
		ft::map<pair::first_type, pair::second_type> map2(p4, p4 + size4);
		print_map_content(map.begin(), map.end());
		print_map_content(map2.begin(), map2.end());
		std::cout << std::endl;
		ft::swap(map, map2);
		print_map_content(map.begin(), map.end());
		print_map_content(map2.begin(), map2.end());
	}
}