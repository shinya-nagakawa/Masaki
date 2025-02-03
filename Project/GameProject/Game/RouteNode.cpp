#include "RouteNode.h"

RouteNode::RouteNode(const CVector3D& pos) 
	: m_pos(pos){
}

void RouteNode::LinkNode(RouteNode* next) {
	m_next.push_back(next);
}

RouteNode* RouteNode::GetNext(int idx) const{
	if (idx >= GetNextSize()) return nullptr;
	return m_next[idx];
}

int RouteNode::GetNextSize() const{
	return m_next.size();
}

std::vector<RouteNode*> RouteNode::GetNextList() const{
	return m_next;
}

CVector3D RouteNode::GetPos() const{
	return m_pos;
}
