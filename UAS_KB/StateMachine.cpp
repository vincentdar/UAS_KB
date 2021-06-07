#include "StateMachine.h"

namespace UAS_KB
{
	void UAS_KB::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		m_isAdding = true;
		m_isReplacing = isReplacing;

		m_newState = std::move(newState);
	}

	void UAS_KB::StateMachine::RemoveState()
	{
		m_isRemoving = true;
	}

	void UAS_KB::StateMachine::ProcessStateChanges()
	{
		if (m_isRemoving && !m_states.empty())
		{
			//Logger::PrintLn("Removed a stack");
			m_states.pop();
			if (!m_states.empty())
			{
				m_states.top()->VResume();
			}
			else
			{
				m_stackEmpty = true;
			}
			m_isRemoving = false;
		}

		if (m_isAdding)
		{
			
			if (!m_states.empty())
			{
				if (m_isReplacing)
				{
					//Logger::PrintLn("Replaced and add a new stack");
					m_states.pop();
				}
				else
				{
					//Logger::PrintLn("Added a new stack");
					m_states.top()->VPause();
				}
			}

			m_states.push(std::move(m_newState));
			m_states.top()->VInit();
			m_isAdding = false;
		}
	}

	StateRef& UAS_KB::StateMachine::GetActiveState()
	{
		return m_states.top();
	}
	bool StateMachine::StackEmpty()
	{
		return m_stackEmpty;
	}
	int StateMachine::StackAllocated()
	{
		return m_states.size();
	}
}

