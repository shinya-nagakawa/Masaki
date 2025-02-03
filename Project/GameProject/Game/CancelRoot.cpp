#include "CancelRoot.h"

template<typename State>
inline CancelRoot<State>::CancelRoot(State state){

}

template<typename State>
void CancelRoot<State>::SetCancelTiming(int timing){
	m_cancelTiming = timing;
}

template<typename State>
bool CancelRoot<State>::IsCanCancel(State changeState){
	return false;
}
