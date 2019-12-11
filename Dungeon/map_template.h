
/*!
\file
\brief This is my template of something like map

I added everything I need in my program
*/
#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include <utility> 
#include <exception>

template<class INDEX, class INFO>
class MapIt;

/*! \brief This is my map template

You has an INDEX and INFO
You're getting an  ITEM by INDEX*/

template<class INDEX, class INFO>
class Map {
	friend class MapIt<INDEX, INFO>; ///< Iterator for this class
private:
	static const int QUOTA = 10; ///< Additional memory that allocates when the array is full
	int SIZE,///< How many items you can put now
		n; ///< Current amount of items
	std::pair<INDEX, INFO> *arr; ///< My array of information
	int getPosition(const INDEX&);
public:
	Map() :SIZE(QUOTA), n(0), arr(new std::pair<INDEX, INFO>[QUOTA]) {};
	Map(const Map<INDEX, INFO> &);
	~Map() { delete[] arr; };
	Map<INDEX, INFO>& operator =(const Map<INDEX, INFO> &);
	INFO & operator[](const INDEX &); ///l
	const INFO operator[] (const INDEX &) const; ///r
	int add( INDEX , INFO );
	typedef MapIt<INDEX, INFO> Iterator;
	Iterator begin();
	Iterator end();
	Iterator find(const INDEX &) const;
};

#endif
/*! \brief Returns the position of chosen INDEX
\param INDEX - what do you want to find
\return index in the array if there is an such INDEX, -1 if there is no such INDEX*/

template<class INDEX, class INFO>
inline int Map<INDEX, INFO>::getPosition(const INDEX &s)
{
	for (int i = 0; i < n; ++i) {
		if (arr[i].first == s)
			return i;
	}
	return -1;
}
/*! \brief Copy Constructor*/
template<class INDEX, class INFO>
inline Map<INDEX, INFO>::Map(const Map<INDEX, INFO>& a):SIZE(a.SIZE), n(a.n), arr(new std::pair<INDEX,INFO> [a.SIZE])
{
	for (int i = 0; i < a.SIZE; ++i) {
		arr[i] = a.arr[i];
	}
}
/*!\brief Operator overload =, copying*/
template<class INDEX, class INFO>
inline Map<INDEX, INFO>& Map<INDEX, INFO>::operator=(const Map<INDEX, INFO>& a)
{
	if (this != &a) {
		delete[] arr;
		arr = new std::pair<INDEX, INFO>[a.SIZE];
		SIZE = a.SIZE;
		n = a.n;
		for (int i = 0; i < a.SIZE; ++i) {
			arr[i] = a.arr[i];
		}
	}
	return *this;
}
/*!\brief Operator overload []

If there is no ITEM with such INDEX, it throws an exception
Else it returns the INFO
*/
template<class INDEX, class INFO>
inline INFO & Map<INDEX, INFO>::operator[](const INDEX &s) throw (std::exception)
{
	int i = getPosition(s);
	if (i < 0)
		throw std::exception("Invalid index");
	return arr[i].second;
}
/*!\brief Operator overload [] for const

If there is no ITEM with such INDEX, it throws an exception
Else it returns the INFO
*/
template<class INDEX, class INFO>
inline const INFO Map<INDEX, INFO>::operator[](const INDEX &s) const throw(std::exception)
{
	int i = getPosition(s);
	if (i < 0)
		throw std::exception("Invalid index");
	return arr[i].second;
}
/*!\brief This functions allows you to add an item with INDEX and INFO

There is such function because I can't normally overload []
*/
template<class INDEX, class INFO>
inline int Map<INDEX, INFO>::add(INDEX index,INFO info)
{
	int i = getPosition(index);
	if (i < 0) {
		i = n;
		if (n >= SIZE) {
			std::pair<INDEX, INFO> *old = arr;
			arr = new std::pair<INDEX, INFO>[SIZE += QUOTA];
			for (int j = 0; j < n; ++j)
				arr[j] = old[j];
			delete[] old;
		}
		arr[i].first = index;
	}
	arr[i].second = info;
	++n;
	return 0;
}
/*!\brief Where iterator should start*/
template<class INDEX, class INFO>
inline MapIt<INDEX,INFO> Map<INDEX, INFO>::begin()
{
	return MapIt<INDEX, INFO>(this->arr);
}
/*!\brief Where iterator should stop*/
template<class INDEX, class INFO>
inline MapIt<INDEX, INFO> Map<INDEX, INFO>::end()
{
	return MapIt<INDEX, INFO>(this->arr + n);
}
/*! \brief Allows to find an INFO by the INDEX*/
template<class INDEX, class INFO>
inline MapIt<INDEX, INFO> Map<INDEX, INFO>::find(const INDEX &s) const
{
	int i = getPosition(s);
	if (i < 0)
		i = n;
	return MapIt<INDEX, INFO>(this->arr + i);
}

/*!\brief This is a class iterator for my map*/
template<class INDEX, class INFO>
class MapIt {
private:
	std::pair <INDEX, INFO> *cur; ///< Current position of iterator
public:
	MapIt() :cur(0) {};
	MapIt(std::pair <INDEX, INFO> *a) :cur(a) {  };
	int operator !=(const MapIt<INDEX, INFO> &) const;
	int operator ==(const MapIt<INDEX, INFO> &) const;
	std::pair <INDEX, INFO>& operator *();
	std::pair <INDEX, INFO> *operator ->();
	MapIt<INDEX, INFO> & operator ++();
	MapIt<INDEX, INFO> & operator ++(int);
};

/*!\brief Overload operator !=*/
template<class INDEX, class INFO>
inline int MapIt<INDEX, INFO>::operator!=(const MapIt<INDEX, INFO>&it) const
{
	return cur != it.cur;
}
/*!\brief Overload operator ==*/
template<class INDEX, class INFO>
inline int MapIt<INDEX, INFO>::operator==(const MapIt<INDEX, INFO>&it) const
{
	return cur == it.cur;
}
/*!\brief Overload operator * */
template<class INDEX, class INFO>
inline std::pair<INDEX, INFO>& MapIt<INDEX, INFO>::operator*()
{
	return *cur;
}
/*!\brief Overload operator -> */
template<class INDEX, class INFO>
inline std::pair<INDEX, INFO>* MapIt<INDEX, INFO>::operator->()
{
	return cur;
}
/*!\brief Overload operator ++ prefix*/
template<class INDEX, class INFO>
inline MapIt<INDEX, INFO>& MapIt<INDEX, INFO>::operator++()
{
	++cur;
	return *this;
}
/*!\brief Overload operator ++ postfix*/
template<class INDEX, class INFO>
inline MapIt<INDEX, INFO>& MapIt<INDEX, INFO>::operator++(int)
{
	MapIt<INDEX, INFO> res(*this);
	++cur;
	return res;
}
