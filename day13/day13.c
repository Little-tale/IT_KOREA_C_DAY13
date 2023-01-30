#include"../../headers/structure.h"


// 이전의 자료구조 -> 변수 , 배열, 포인터, 구조체, 백터
//  백터의 단점 : 커다란 메모리 용량... 정확히는 배열의 단점
// 저장공간 -> 기본적으로 탐색을 한다. -> 용량이 크다면 쉬울까요? -> 쉽지 않습니다. ->
// 리스트 -> 백터의 한계를 극복하기 위해 만들어진 자료구조

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
	return Allocation(sizeof(List)); //동적할당과 기본 크기가 생성되고, 빈공간은 0으로 채운다.
}

Void ReleaseList(pList this)
{
	pNode now = this->root;	// 첫번째로 가지고 있는 주소를 now에 답고 
	pNode rem;				// 
	while (now != 0)		// 나우가 0이 아니라면 동작
	{
		rem = now;			// 
		now = now->next;	// 나우에 다음 주소를
		free(rem->data);	// 렘에 주소에 정보 삭제
		free(rem);			// 동적할당 해제 
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
			now = now->next; // 이 반복문이 종료된 나우가 마지막 데이터가 된다.
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
	pControlData cd = Allocation(sizeof(ControlData)); // cd를 동적할당
	cd->number = number; //cd안에 넘버라는 것에 입력받은 숫자를 넣고 반환
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

// 리스트라는 자료구조는 장점과 단점이 있다.
// 데이터를 필요로 할때 필요한 만큼 만들기에 생성 및 삭제에 있어서 자유롭다.
// 생성을 자유롭게 하기위해 파편화 시켰기 때문에 한개의 데이터를 선택하는데 비용이 높다.


// 양방향 연결리스트




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




// 내가 숫자를 입력하면 무한히 숫자를 저장하다 0으,ㄹ 입력하면 지금까지 입력한 숫자들을 모두 출력하는 프로그램


// 리스트 정보의 크기 -> 20바이트라고 치면 주소저장도 해야하는 8바이트도 필요하다 치고
// 20 + 8전주소 + 8다음주소 -> 일반적인 배열보다 는 큰 용량이지만 벡터보다는 작다.

//Void main()
//{
//	pList list = CreateList(); //내가 만든 리스트포인터인 list를 만들었다.
//	//printf_s("%p", list); // 주소값이 나오는 것을 확인할수 있다.
//	//printf_s("%d", list->root); // 기본으로 초기화 된 0을 확인할수 있다.
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
//		test = Scan("입력하실 숫자 : ");
//		if(test != 0)InsertList(list2, CD(test));
//		else {
//			printf("종료합니다. \n");
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


// 숫자를 무한히 입력하다 0을 입력하면 입력을 중지하시오
// 입력이 중지되면 지금까지 입력한 모근 숫자 중 짝수는 그대로 출력하소
// 홀수는 *10 을 해서 출력하시오

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
		select = Scan("숫자를 입력하세요~");
		if (select == 0) {
			printf("종료합니다."); break;
		}
		InsertList(list, CD(select));
	}
	ActionList(list,ShowCD);
	//pControlData fcd = FindNodeList(list, list->root->data %2 ==0 );


	
	



	ReleaseList(list);
	ReleaseList(list2);

}
