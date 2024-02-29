# Floorplan-Algorithm

## Basic concept
The whole algorithm is based on the idea presented [in this article](https://www.mcs.anl.gov/~itf/dbpp/text/node21.html). 
Basically each element on the floorplan has one or more implementations(sizes/dimensions) and has defined where on the floorplan it has to be(neighboring elements).
Also:
- The floorplan is a rectangle
- All elements are rectangles
- There is no defined maximum size nor dimension. The algorithm just finds the best implementation for each element in order to achieve the smallest floorplan area.

In the algorithm an element is defined as a *Type* and the implementation is a *Variant*.

Unfortunetly the algorithm isn't perfect. You might create physically impossible creations and the algorithm would still calculate them.

## GUI
The algorithm has a GUI version, which can be found [here](https://github.com/MrChrisFix/Floorplan-Optimizer).

There you can create types on your own, see the variant dimensions, save the created types to an XML and more.

## Usage
### 1. As console application
The compiled executable can be run by console command in the following way:

``` FloorplanAlgorithm -f <XML file path> [-t <thread count>] ```

The file path is non-optional, but the thread count is. By default the thread count is set to 1, so the algorithm works sequential.  
If you want to know the structure of the XML file you can look the the `templateXML.xml` file.


### 2. Use it in your own code

There are only 1-2 classes you have to use. 
- One of them is `XMLFileManager`, which is used for saving and reading XML files with defined types.
The structure of the XML file can be seen e.g. in the `templateXML.xml` file.
- The second (and most important) is `AlgorithmManager`. There are 2 methods which have to be used to start optimization process. 
The first one is `setTypes(...)`, which is a setter for the types on which the algorithm works. It takes a `std::vector<FPA::Type*>` as the argument.
The second one is `StartCalculations(...)`, which takes 2 arguments: 
  - an int for the amount of threads the algoritm should use for multithreading;
  - a bool asking if the algorithm should use multithreading. If false then it ignores the first parameter.

  The return value is a `ResultStruct` object, which includes optimization time, a `std::vector<FPA::Variant*>`, which is the best combination of variants, and the final height and width of the best combination.
  
  One important note is that the `AlgorithmManager` doesn't delete the given Types in the vector on destruction. You have to release the memory outside the algorithm on your own.
  
If you don't want to load the types from an XML file and instead create them at runtime you can look at how to do it in the `TypeVectorCreator(...)` method found in the `TimeTester` class. 
The method creates random types, variants and requirements.
