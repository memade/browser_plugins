#if !defined(__22A48A42_3D94_488E_AE8C_9E2CABA2C1AB__)
#define __22A48A42_3D94_488E_AE8C_9E2CABA2C1AB__

namespace local {

	class UICefApp : public IApp {
	public:
		UICefApp();
		virtual ~UICefApp();
	public:
		void Init() override final;
		void Cleanup() override final;
	};

	class UIApp : public IApp {
	public:
		UIApp();
		virtual ~UIApp();
	public:
		void Init() override final;
		void Cleanup() override final;
	};


}///namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 18 Feb 2023 17:36:55 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__22A48A42_3D94_488E_AE8C_9E2CABA2C1AB__


