#include"../../headers/structure.h"


// ������ �ڷᱸ�� -> ���� , �迭, ������, ����ü, ����
//  ������ ���� : Ŀ�ٶ� �޸� �뷮... ��Ȯ���� �迭�� ����
// ������� -> �⺻������ Ž���� �Ѵ�. -> �뷮�� ũ�ٸ� ������? -> ���� �ʽ��ϴ�. ->
// ����Ʈ -> ������ �Ѱ踦 �غ��ϱ� ���� ������� �ڷᱸ��

// int arr[4] -> int a,b,c,d;

typedef struct ControlData
{
	Dec number;
}ControlData,*pControlData;

typedef struct Node
{
	pControlData data;
	struct Node* prev;
	struct Node* next;
}Node,*pNode;


typedef struct List {
	pNode root;
}List,*pList;

pList CreateList()
{
	return Allocation(sizeof(List)); //�����Ҵ�� �⺻ ũ�Ⱑ �����ǰ�, ������� 0���� ä���.
}

Void ReleaseList(pList this)
{
	pNode now = this->root;	// ù��°�� ������ �ִ� �ּҸ� now�� ��� 
	pNode rem;				// 
	while (now != 0)		// ���찡 0�� �ƴ϶�� ����
	{
		rem = now;			// 
		now = now->next;	// ���쿡 ���� �ּҸ�
		free(rem->data);	// ���� �ּҿ� ���� ����
		free(rem);			// �����Ҵ� ���� 
	}
	free(this);
}

Void InsertList(pList list, pControlData data)
{
	pNode node = Allocation(sizeof(Node));
	node->data = data;
	if (list->root)
	{
		pNode now = list->root;
		while (now->next != 0)
		{
			now = now->next; // �� �ݺ����� ����� ���찡 ������ �����Ͱ� �ȴ�.
		}
		now->next = node;
		node->prev = now;
	}
	else {
		list->root = node;
	}
}

pControlData CD(Dec number)
{
	pControlData cd = Allocation(sizeof(ControlData)); // cd�� �����Ҵ�
	cd->number = number; //cd�ȿ� �ѹ���� �Ϳ� �Է¹��� ���ڸ� �ְ� ��ȯ
	return cd;
}


typedef Void(*pAction)(pControlData);

Void ActionList(pList list, pAction action)
{
	pNode now = list->root;
	while (now != 0)
	{
		action(now->data);
		now = now->next;
	}

}

Void ShowCD(pControlData data)
{
	printf("%d > ", data->number);
}

Void ShowCDx10(pControlData data)
{
	printf("%d > ", data->number * 10);
}

// ����Ʈ��� �ڷᱸ���� ������ ������ �ִ�.
// �����͸� �ʿ�� �Ҷ� �ʿ��� ��ŭ ����⿡ ���� �� ������ �־ �����Ӵ�.
// ������ �����Ӱ� �ϱ����� ����ȭ ���ױ� ������ �Ѱ��� �����͸� �����ϴµ� ����� ����.


// ����� ���Ḯ��Ʈ




Dec CompareCD(pControlData cd1, pControlData cd2)
{
	return cd1->number == cd2->number;
}






pNode FindNodeList(pList list, pControlData data)
{
	pNode now = list->root;
	while (now -= 0) {
		if (CompareCD(now->data, data))
		{
			free(data);
			return now;
		}
		now = now->next;
	}
	
	free(data);
	
	return 0;
}


pControlData FindCDList(pList list, pControlData data) {
	pNode node = FindNodeList(list, data);
	if (node) return node->data;
	return 0;
}


Void RemoveList(pList list, pControlData data)
{
	pNode node = FindNodeList(list, data);
	if (node)
	{
		if (node->prev) node->prev->next = node->next;
		else list->root = node->next;
		if (node->next) node->next->prev = node->prev;

		/*node->prev->next = node->next;
		node->next->prev = node->prev;*/

		free(node->data);
		free(node);
	}
}




// ���� ���ڸ� �Է��ϸ� ������ ���ڸ� �����ϴ� 0��,�� �Է��ϸ� ���ݱ��� �Է��� ���ڵ��� ��� ����ϴ� ���α׷�


// ����Ʈ ������ ũ�� -> 20����Ʈ��� ġ�� �ּ����嵵 �ؾ��ϴ� 8����Ʈ�� �ʿ��ϴ� ġ��
// 20 + 8���ּ� + 8�����ּ� -> �Ϲ����� �迭���� �� ū �뷮������ ���ͺ��ٴ� �۴�.

//Void main()
//{
//	pList list = CreateList(); //���� ���� ����Ʈ�������� list�� �������.
//	//printf_s("%p", list); // �ּҰ��� ������ ���� Ȯ���Ҽ� �ִ�.
//	//printf_s("%d", list->root); // �⺻���� �ʱ�ȭ �� 0�� Ȯ���Ҽ� �ִ�.
//	
//	for (Dec i = 0; i < 1000; ++i)
//	{
//		InsertList(list, CD(i));
//	}
//
//	ActionList(list, ShowCD);
//
//
//	pList list2 = CreateList();
//	Dec test = 0;
//	while (1)
//	{
//		test = Scan("�Է��Ͻ� ���� : ");
//		if(test != 0)InsertList(list2, CD(test));
//		else {
//			printf("�����մϴ�. \n");
//			break;
//		}
//	}
//
//
//	pControlData cd = FindCDList(list, CD(4));
//	if (cd)ShowCD(cd);
//
//
//	
//
//
//
//
//	RemoveList(list2, CD(4));
//	RemoveList(list2, CD(5));
//	RemoveList(list2, CD(6));
//
//	ActionList(list2, ShowCD);
//
//
//
//	InsertList(list, CD(4));
//	InsertList(list, CD(5));
//
//	ReleaseList(list); ReleaseList(list2);
//}
//


// ���ڸ� ������ �Է��ϴ� 0�� �Է��ϸ� �Է��� �����Ͻÿ�
// �Է��� �����Ǹ� ���ݱ��� �Է��� ��� ���� �� ¦���� �״�� ����ϼ�
// Ȧ���� *10 �� �ؼ� ����Ͻÿ�

Dec Compare_2(pControlData cd)
{
	if (cd->number % 2 == 0)return 1;
	return 0;
}
Dec Compare_1(pControlData cd)
{
	if (cd->number % 2 == 1)return 1;
	return 0;
}

typedef Dec(*pCompare)(pControlData);

Void ActionCompareList(pList list, pAction action) {
	pNode now = list->root;
	while (now != 0)
	{
		//if(comp())
	}
}

Void main()
{
	pList list = CreateList();
	pList list2 = CreateList();

	Dec select = 0;
	while (1)
	{
		select = Scan("���ڸ� �Է��ϼ���~");
		if (select == 0) {
			printf("�����մϴ�."); break;
		}
		InsertList(list, CD(select));
	}
	ActionList(list,ShowCD);
	//pControlData fcd = FindNodeList(list, list->root->data %2 ==0 );


	
	



	ReleaseList(list);
	ReleaseList(list2);

}
