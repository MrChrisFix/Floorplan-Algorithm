#pragma once

namespace FPA {

class Type; //<- avoiding a #include deadlock

class Variant
{
private:

	unsigned int height, width;			/// The  height and width of the variant
	Type* type;							/// The parent Type of the variant

public:
	
	/**
	 * Constructor
	 * @param hei The initial height
	 * @param wid The initial width
	 * @param parentType The parent Type
	*/
	Variant(unsigned hei, unsigned wid, Type* parentType);
	/**
	 * Destructor
	*/
	~Variant();

	/**
	 * Getter of height
	 * @return Height of the variant
	*/
	unsigned GetHeight();

	/**
	 * Height setter
	 * @param hei The new height of the variant
	*/
	void SetHeight(unsigned hei);

	/**
	 * Getter of width
	 * @return Width of the variant
	*/
	unsigned GetWidth();

	/**
	 * Width setter
	 * @param wid The new width of the variant 
	*/
	void SetWidth(unsigned wid);

	/**
	 * Getter of parent Type
	 * @return The parent Type object
	*/
	Type* GetType();
};

} //namespace FPA