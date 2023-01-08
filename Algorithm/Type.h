#pragma once
#include <vector>
#include "Variant.h"
#include <string>

namespace FPA {

class Type
{
private:
	std::vector<Variant*> variants; /// Vector with all variants of the type

	std::string name;				/// Only for cosmetic purposes

public:
	Type(std::string typeName);
	~Type();

	//Requirements
	std::vector<Type*> right;		/// Types required to be on the right
	std::vector<Type*> down;		/// Types required to be down
	std::vector<Type*> left;		/// Types required to be on the left
	std::vector<Type*> up;			/// Types required to be up

	/**
	 * Name setter 
	 * @param newName The new name the type should have
	*/
	void setName(std::string newName);

	/**
	 * Name getter
	 * @return The name of the type
	*/
	std::string GetName();

	/**
	 * Getter for the vector of variants
	 * @return Vector of Variants
	*/
	std::vector<Variant*> GetVariants();

	/**
	 * Add new Variant to the vector 
	 * @param variant The variant that shuld be added
	*/
	void AddVariant(Variant* variant);

	/**
	 * Created and add a new Variant to the vector
	 * @param varWidth The width of the new Variant
	 * @param varHeight The height of the new Variant
	*/
	void AddVariant(unsigned varWidth, unsigned varHeight);

	/**
	 * Removes the Variant from the vector
	 * @param variant The variant that should be removed
	 */
	void RemoveVariant(Variant* variant);

	/**
	 * Adds a requirement to the type invoked on and the type given
	 * @param side The side of the requirement. 
	 *			   Options: 'U'(Up), 'D'(Down), 'R'(Right), 'L'(Left)
	 * @param type The type of the requirement
	 * @param onBoth The requirement should be added on the invoked Type and given Type
	*/
	void AddRequirement(char side, Type* type, bool onBoth = true);

	/**
	 * Removes the given requirement from requirements vector
	 * @param toRemove The type which should be removed
	 * @param onBoth Should the other requirement delete us
	 */
	void RemoveRequirement(Type* toRemove, bool onBoth = false);
};

} //namespace FPA