#pragma once

namespace UAS_KB
{
	class IState
	{
	public:
		virtual void VInit() = 0;
		virtual void VDraw(float dt) = 0;
		virtual void VHandleInput() = 0;
		virtual void VUpdate(float dt) = 0;
		virtual void VResume() = 0;
		virtual void VPause() = 0;
		virtual void VExit() = 0;

		virtual ~IState() {}
	};
}