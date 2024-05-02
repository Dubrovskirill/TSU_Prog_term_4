#include<vector>
#include <thread>
#include<assert.h>
#include <vector>
#include<random>
#include "AvlTree.h"
#include "AvlTreeTester.h"

int main()
{
    

   // srand(time(0));
   // AvlTreeTester tester(false);
   // tester.test(10);

   // return 0;


   // auto printList = [](std::list<BinaryTree::Node*> list) {
   //     std::cout << '{';
   //     for (auto it = list.begin(); it != list.end();) {
   //         std::cout << (*it)->getKey() << (++it == list.end()
   //             ? "}\n"
   //             : ", ");
   //     }
   // };

   // AvlTree boo;

   // int size = -1;
   // std::cout << "tree size: ";
   // std::cin >> size;

   // std::vector<int> nums(size);

   ///* std::cout << '{';*/
   // int num = INT_MIN;
   // for (auto it = nums.begin(); it != nums.end(); ++it) {
   //     num = rand() % (size * 2);
   //     while (std::find(nums.begin(), nums.end(), num) != nums.end()) {
   //         num = rand() % (size * 2);
   //     }
   //     *it = num;
   //    /* std::cout << (*it) << (it + 1 == nums.end()
   //         ? ""
   //         : ", ");*/
   // }
   ///* std::cout << '}' << std::endl;*/

   // int sleepTime = 0;
   //// std::cout << "sleep time(seconds): ";
   //// std::cin >> sleepTime;
   // sleepTime *= 1000;

   // char printAnswer = 'n';
   //// std::cout << "wanna print tree? y/n: ";
   //// std::cin >> printAnswer;

   // std::cout << std::endl;

   // int currentSize = -1;
   // for (auto it = nums.begin(); it != nums.end(); ++it) {
   //     boo.add(*it);
   //     currentSize = boo.nodeCount();

   //     /*std::cout << "added - " << *it << "\t current size - " << currentSize << std::endl;
   //     std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
   //     if (printAnswer == 'y') {
   //         std::cout << "printing tree. . ." << std::endl;
   //         boo.print_3(boo.root());
   //     }*/

   //     assert(boo.find(*it));
   //     assert(boo.find(*it)->getKey() == *it);
   //     assert(boo.isBalanced());

   //     /*std::cout << std::endl;
   //     std::cout << std::endl;
   //     std::cout << std::endl;*/
   // }
   // std::cout << "ADD:success" << std::endl;
   ///* std::cout << "\t\t\tREMOVE TIME!" << std::endl;

   // std::cout << std::endl;
   // std::cout << std::endl;
   // std::cout << std::endl;*/

   // currentSize = -1;
   // int current = INT_MIN;
   // int iterCount = 0;
   // auto it = nums.begin();
   // while (!nums.empty()) {
   //     ++iterCount;
   //     current = *it;
   //   
   //     boo.remove(*it);
   //     nums.erase(it);

   //     /*std::cout << "step - " << iterCount;
   //     std::cout << "\t removed - " << current << "\t current size - " << boo.nodeCount() << std::endl;
   //     std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
   //     if (printAnswer == 'y') {
   //         std::cout << "printing tree. . ." << std::endl;
   //         boo.print_3(boo.root());
   //     }*/

   //     currentSize = boo.nodeCount();
   //     assert(currentSize == nums.size());
   //     assert(!boo.find(current));
   //     assert(boo.isBalanced());

   //     //std::cout << std::endl;
   //     //std::cout << std::endl;
   //     //std::cout << std::endl;

   //     it = nums.begin();
   // }
   // std::cout << "REMOVE:success";
   // return 0;





















	AvlTree tr;
	/*int arr[13] = { 10,20,40,35,38,36,5, 13, 15, 56, 12, 67,689 };
	for(int i=0;i<13;++i)
	{
		tr.add(arr[i]);
		tr.print_3(tr.root());
		std::cout << std::endl;
	}*/
	/*int arr[12] = { 10,6,16,2,8,14,20,1,4,12,18,25 };
	for (int i = 0; i < 12; ++i)
	{
		tr.add(arr[i]);
		tr.print_3(tr.root());
		std::cout << std::endl;
	}

	
	for (int i = 11; i >= 0; --i)
	{
		tr.remove(arr[i]);
		tr.print_3(tr.root());
		std::cout << std::endl;
	}*/
	/*int input;
	std::cin >> input;
	std::cout << std::endl;
	while (input != -1) {
		tr.add(input);
		tr.print_3(tr.root());
		std::cin >> input;
		std::cout << std::endl;
	}*/

	/*int arr[7] = {10,20,40,35,38,36,5 };
	for (int i = 0; i < 7; ++i)
	{
		tr.add(arr[i]);
		tr.print_3(tr.root());
	}*/

	int arr[13] = { 10,20,40,35,38,36,5, 13, 15, 56, 12, 67,689 };
	for (int i = 0; i < 13; ++i)
	{
		tr.add(arr[i]);
		tr.print_3(tr.root());
		std::cout << std::endl;
	}
	if (tr.isBalanced()) {
		std::cout << "isBalansed";
	}
	else {
		std::cout << "BLABLABLA";
	}
	
}