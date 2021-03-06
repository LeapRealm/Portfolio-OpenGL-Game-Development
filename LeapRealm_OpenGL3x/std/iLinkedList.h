#pragma once

struct iNode
{
	void* data;
	iNode* prev;
};

typedef void (*MethodDeleteObject)(void* data);

class iLinkedList
{
public:
	iLinkedList(MethodDeleteObject mdo = nullptr);
	virtual ~iLinkedList();

	void addObject(void* data);
	void addObject(int index, void* data);

	void removeObject(int index);
	void removeObject(void* data);
	void removeAllObjects();

	void* unlinkObject(int index);
	void* unlinkObject(void* data);

	void* getObjectByIndex(int index);
	int getIndexByObject(void* data);

public:
	iNode* tail;
	int count;

	MethodDeleteObject method;
};
