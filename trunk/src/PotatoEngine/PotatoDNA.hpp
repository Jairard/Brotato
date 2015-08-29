#ifndef __POT_POTATODNA__
#define __POT_POTATODNA__

#include <list>

namespace Pot
{

class Stem;
class Potato;

// DNA<T> (for cells) ?
class PotatoDNA
{
	friend class Stem;
	friend class Potato;

	public:
		explicit PotatoDNA(Potato* potato); // private ?
		PotatoDNA(const PotatoDNA& other);
		~PotatoDNA();

		bool isValid() const { return m_potato != nullptr; }

		void operator=(const PotatoDNA& other);
		void operator=(const Potato* potato);
		Potato* operator->();

	private:
		void onPotatoShutdown(const Potato* potato);

	private:
		Potato* m_potato;
};

}

#endif
