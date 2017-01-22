#define kPin_IRIDIUM_RX		18
#define kPin_IRIDIUM_TX		19
#define kPin_IRIDIUM_SLEEP  10

class Avionics {
public:
	int initAvionics();
	void demoCom(char message);
private:
	int initCom();
}

//factory class