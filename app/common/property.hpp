#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <string>

/*
		Property<string, double> K("Strike Price", 65.0);
		Property<string, double> sig("Volatility", 0.30);

		double example = sig() * sqrt(K);
*/
template <class Name = std::string_view, class Type = int>
class Property
{
public:
	Property();
	Property(const Name &rhs_name, const Type &rhs_type);
	Property(const Property<Name, Type> &rhs);

	virtual ~Property();

	virtual Type operator()() const;
	virtual void operator()(const Type &rhs_type);

	virtual Name name() const;
	virtual void name(const Name &new_name);

	bool operator==(const Property<Name, Type> &rhs);

private:
	Name name_;
	Type type_;
};

#endif
