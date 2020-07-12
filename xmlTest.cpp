#include <tinyxml2.h>
#include <cassert>
#include <vector>

using namespace tinyxml2;

void SetData()
{
	//XMLDocument and  XMLElement is a XMLNode
	XMLDocument doc;

	//create a new root Node
	XMLNode* pRoot = doc.NewElement("Root");

	//attach the Root to this doc
	doc.InsertFirstChild(pRoot);

	//create a element
	XMLElement* pElement = doc.NewElement("IntValue");
	pElement->SetText(10);
	pRoot->InsertFirstChild(pElement);

	std::vector<int> items = { 1,2,3,4,5,6 };

	pElement = doc.NewElement("List");
	for (auto item : items)
	{
		//insert list children
		XMLElement* pListElement = doc.NewElement("Item");
		pListElement->SetText(item);
		pElement->InsertEndChild(pListElement);
	}

	pElement->SetAttribute("itemCount", items.size());

	auto p1 = pRoot->InsertFirstChild(pElement);

	//printer
	XMLPrinter printer;
	doc.Print(&printer);
	auto str = printer.CStr();

	//save file
	doc.SaveFile("test.xml");
}

void GetData()
{
	XMLDocument doc;
	auto rt = doc.LoadFile("test.xml");
	assert(rt == XML_SUCCESS);

	//get the Root of this doc
	XMLNode* pRoot = doc.FirstChild();

	//get element by name
	XMLElement* pElement = pRoot->FirstChildElement("IntValue");
	int nVal = 0;
	pElement->QueryIntText(&nVal);


	//list ,µÝ¹é²éÑ¯
	pElement = pRoot->FirstChildElement("List");
	XMLElement* pListElement = pElement->FirstChildElement("Item");
	std::vector<int> vecList;
	while (pListElement != nullptr)
	{
		int nVal = 0;
		pListElement->QueryIntText(&nVal);
		vecList.push_back(nVal);
		pListElement = pListElement->NextSiblingElement("Item");
	}

	return;
	//auto val = doc.FirstChildElement("note")->FirstChildElement()->GetText();

}

int main()
{
	GetData();


	XMLPrinter printer;
	/*doc.Print(&printer);
	auto str = printer.CStr();*/

	/*printer.OpenElement("foo");
	printer.PushAttribute("name", "szw");
	printer.CloseElement();

	auto str = printer.CStr();*/



	system("pause");
}