#ifndef __UI__
#define __UI__

#include <vector>
#include <SFML/Graphics.hpp>

class CheckBox;
struct Settings;

class UI: public sf::Drawable, public sf::View
{
	public:
		UI(const Settings& settings);
		virtual ~UI();

	protected:
		static const char* FONT_FILE;
		sf::Font _font;
		bool _isFontLoaded;
		sf::RectangleShape _background;
		std::vector<CheckBox*> _checkboxes;

	private:
		void build(const Settings& settings);
    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    	void updateBackground(void);
};

class CheckBox: public sf::Drawable, public sf::Transformable
{
	public:
		CheckBox(bool checked, const char* txt, ...);
		virtual ~CheckBox() {}

	protected:
		bool _checked;
		sf::Text _text;

	private:
    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
