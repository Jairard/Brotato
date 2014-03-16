#include <cstdio>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "test.hpp"
#include "render.hpp"

b2Vec2 ConvertScreenToWorld(int32 x, int32 y);
sf::Vector2f sfConvertScreenToWorld(int32 x, int32 y);
b2AABB computeWorldAABB(b2Vec2 margin);
void updateView(bool computeAABB=true);
unsigned char key2char(sf::Keyboard::Key key);

void init(void);
void handleEvents(void);
void update(void);
void drawControls(DebugRenderer& renderer);
//void drawUI(void);
bool keyPressed(sf::Keyboard::Key key);
bool keyReleased(sf::Keyboard::Key key);
void mousePressed(sf::Mouse::Button button, int x, int y);
void mouseReleased(sf::Mouse::Button button, int x, int y);
void mouseMotion(int x, int y);

sf::RenderWindow* window = 0;

namespace
{
	int32 testIndex = 0;
	int32 testSelection = 0;
	int32 testCount = 0;
	TestEntry* entry;
	Test* test;
	Settings settings;
	int32 width = 640;
	int32 height = 480;//640;
	int32 framePeriod = 16;
	int32 mainWindow;
	float settingsHz = 30.;
	float32 viewZoom = 1.0f;
	sf::Vector2f viewSize;
	sf::Vector2f viewCenter;
	int tx, ty, tw, th;
	bool rMouseDown;
	sf::Vector2f lastp;
	b2AABB worldAABB;
	bool displayControls = false;
	float fpsRefreshTime = 0.5;
	int fps = settingsHz, frames = 0;

	sf::View physicsView;//, uiView;
}

int main(int argc, char* argv[])
{	
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	init();
	DebugRenderer renderer;
	sf::Clock clock, fpsClock;

	while (window->isOpen())
	{
		handleEvents();

		window->clear();
		update();
		renderer.DrawString(window->getSize().x - 75, 10, "%3d FPS", fps);
		drawControls(renderer);

		window->display();

		frames++;

		float elapsed = clock.getElapsedTime().asSeconds();
		sf::Time toSleep = sf::seconds(1./settingsHz - elapsed);

		if (toSleep.asSeconds() > 0)
			sf::sleep(toSleep);
		clock.restart();

		if (fpsClock.getElapsedTime().asSeconds() > fpsRefreshTime)
		{
			fps = frames/fpsRefreshTime;
			frames = 0;
			fpsClock.restart();
		}
	}

	delete window;

	return EXIT_SUCCESS;
}

sf::Vector2f sfConvertScreenToWorld(int32 x, int32 y)
{
	window->setView(physicsView);
	sf::Vector2f res = window->mapPixelToCoords(sf::Vector2i(x, y));
	res.y = -res.y;
	return res;
}

b2Vec2 ConvertScreenToWorld(int32 x, int32 y)
{
	sf::Vector2f tmp = sfConvertScreenToWorld(x, y);
	return b2Vec2(tmp.x, tmp.y);
}

b2AABB computeWorldAABB(b2Vec2 margin)
{
	b2World* w = test->GetWorld();
	const b2Body* body = w->GetBodyList();
	unsigned int bodyCount = w->GetBodyCount();

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX); 

	while (body != NULL)
	{
		b2Fixture* fixture = (b2Fixture*)body->GetFixtureList();

		while (fixture != NULL)
		{
		    aabb.Combine(aabb, fixture->GetAABB(0));
		    fixture = fixture->GetNext();
		}

		body = body->GetNext();
	}

	aabb.lowerBound -= margin;
	aabb.upperBound += margin;

	return aabb;
}

void updateView(bool computeAABB)
{
	if (computeAABB)
	{
		worldAABB = computeWorldAABB(b2Vec2(5., 5.));
		sf::Vector2f lower(worldAABB.lowerBound.x, worldAABB.lowerBound.y),
		             upper(worldAABB.upperBound.x, worldAABB.upperBound.y);
		viewCenter = (lower+upper) / 2.f;
		viewCenter.y = -viewCenter.y;


		viewSize = sf::Vector2f(worldAABB.upperBound.x-worldAABB.lowerBound.x,
		                        worldAABB.upperBound.y-worldAABB.lowerBound.y);
	}

	sf::Vector2f windowSize(window->getSize());
	sf::FloatRect viewport = physicsView.getViewport();
	float ratio = (viewport.width * windowSize.x) / (viewport.height * windowSize.y);
	float newRatio = viewSize.x / viewSize.y;

	if (newRatio > ratio)
		viewSize.y = viewSize.x / ratio;
	else
		viewSize.x = viewSize.y * ratio;

	/* ? */
	settings.viewCenter = b2Vec2(viewCenter.x, viewCenter.y);

	physicsView.setCenter(viewCenter);
	physicsView.setSize(viewSize * viewZoom);
}

unsigned char key2char(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::A:
			return 'a';
		case sf::Keyboard::B:
			return 'b';
		case sf::Keyboard::C:
			return 'c';
		case sf::Keyboard::D:
			return 'd';
		case sf::Keyboard::E:
			return 'e';
		case sf::Keyboard::F:
			return 'f';
		case sf::Keyboard::G:
			return 'g';
		case sf::Keyboard::H:
			return 'h';
		case sf::Keyboard::I:
			return 'i';
		case sf::Keyboard::J:
			return 'j';
		case sf::Keyboard::K:
			return 'k';
		case sf::Keyboard::L:
			return 'l';
		case sf::Keyboard::M:
			return 'm';
		case sf::Keyboard::N:
			return 'n';
		case sf::Keyboard::O:
			return 'o';
		case sf::Keyboard::P:
			return 'p';
		case sf::Keyboard::Q:
			return 'q';
		case sf::Keyboard::R:
			return 'r';
		case sf::Keyboard::S:
			return 's';
		case sf::Keyboard::T:
			return 't';
		case sf::Keyboard::U:
			return 'u';
		case sf::Keyboard::V:
			return 'v';
		case sf::Keyboard::W:
			return 'w';
		case sf::Keyboard::X:
			return 'x';
		case sf::Keyboard::Y:
			return 'y';
		case sf::Keyboard::Z:
			return 'z';
		case sf::Keyboard::Num0:
			return '0';
		case sf::Keyboard::Num1:
			return '1';
		case sf::Keyboard::Num2:
			return '2';
		case sf::Keyboard::Num3:
			return '3';
		case sf::Keyboard::Num4:
			return '4';
		case sf::Keyboard::Num5:
			return '5';
		case sf::Keyboard::Num6:
			return '6';
		case sf::Keyboard::Num7:
			return '7';
		case sf::Keyboard::Num8:
			return '8';
		case sf::Keyboard::Num9:
			return '9';
		case sf::Keyboard::Escape:
		case sf::Keyboard::LControl:
		case sf::Keyboard::LShift:
		case sf::Keyboard::LAlt:
		case sf::Keyboard::LSystem:
		case sf::Keyboard::RControl:
		case sf::Keyboard::RShift:
		case sf::Keyboard::RAlt:
		case sf::Keyboard::RSystem:
		case sf::Keyboard::Menu:
			return 0;
		case sf::Keyboard::LBracket:
			return '[';
		case sf::Keyboard::RBracket:
			return ']';
		case sf::Keyboard::SemiColon:
			return ';';
		case sf::Keyboard::Comma:
			return ',';
		case sf::Keyboard::Period:
			return '.';
		case sf::Keyboard::Quote:
			return '\'';
		case sf::Keyboard::Slash:
			return '/';
		case sf::Keyboard::BackSlash:
			return '\\';
		case sf::Keyboard::Tilde:
			return '~';
		case sf::Keyboard::Equal:
			return '=';
		case sf::Keyboard::Dash:
			return '-';
		case sf::Keyboard::Space:
			return ' ';
		case sf::Keyboard::Return:
			return '\n';
		case sf::Keyboard::BackSpace:
			return '\b';
		case sf::Keyboard::Tab:
			return '\t';
		case sf::Keyboard::PageUp:
		case sf::Keyboard::PageDown:
		case sf::Keyboard::End:
		case sf::Keyboard::Home:
		case sf::Keyboard::Insert:
		case sf::Keyboard::Delete:
			return 0;
		case sf::Keyboard::Add:
			return '+';
		case sf::Keyboard::Subtract:
			return '-';
		case sf::Keyboard::Multiply:
			return '*';
		case sf::Keyboard::Divide:
			return '/';
		case sf::Keyboard::Left:
		case sf::Keyboard::Right:
		case sf::Keyboard::Up:
		case sf::Keyboard::Down:
			return 0;
		case sf::Keyboard::Numpad0:
			return '0';
		case sf::Keyboard::Numpad1:
			return '1';
		case sf::Keyboard::Numpad2:
			return '2';
		case sf::Keyboard::Numpad3:
			return '3';
		case sf::Keyboard::Numpad4:
			return '4';
		case sf::Keyboard::Numpad5:
			return '5';
		case sf::Keyboard::Numpad6:
			return '6';
		case sf::Keyboard::Numpad7:
			return '7';
		case sf::Keyboard::Numpad8:
			return '8';
		case sf::Keyboard::Numpad9:
			return '9';
		case sf::Keyboard::F1:
		case sf::Keyboard::F2:
		case sf::Keyboard::F3:
		case sf::Keyboard::F4:
		case sf::Keyboard::F5:
		case sf::Keyboard::F6:
		case sf::Keyboard::F7:
		case sf::Keyboard::F8:
		case sf::Keyboard::F9:
		case sf::Keyboard::F10:
		case sf::Keyboard::F11:
		case sf::Keyboard::F12:
		case sf::Keyboard::F13:
		case sf::Keyboard::F14:
		case sf::Keyboard::F15:
		case sf::Keyboard::Pause:
		case sf::Keyboard::KeyCount:
			return 0;
		default:
			return 0;
	}
}

void init()
{
	testCount = 0;
	while (g_testEntries[testCount].createFcn != NULL)
	{
		++testCount;
	}

	testIndex = b2Clamp(testIndex, 0, testCount-1);
	testSelection = testIndex;
	entry = g_testEntries + testIndex;
	test = entry->createFcn();

	char title[256];
	sprintf(title, "SFML - Box2D %d.%d.%d Testbed", b2_version.major, b2_version.minor, b2_version.revision);

	window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	//physicsView.setViewport(sf::FloatRect(0., 0., 1., 0.75));
	//ui.setViewport(sf::FloatRect(0., 0.75, 1., 0.25));

	updateView();
}

void handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if (!keyPressed(event.key.code))
					window->close();
				break;
			case sf::Event::KeyReleased:
				if (!keyReleased(event.key.code))
					window->close();
				break;
			case sf::Event::MouseButtonPressed:
				mousePressed(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
				break;
			case sf::Event::MouseButtonReleased:
				mouseReleased(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
				break;
			case sf::Event::MouseMoved:
				mouseMotion(event.mouseMove.x, event.mouseMove.y);
			default:
				break;
		}
	}
}

void update()
{
	window->setView(physicsView);

	test->SetTextLine(30);
	//b2Vec2 oldCenter = settings.viewCenter;
	settings.hz = settingsHz;
	test->Step(&settings);

	test->DrawTitle(5, 15, entry->name);

	if (testSelection != testIndex)
	{
		testIndex = testSelection;
		delete test;
		entry = g_testEntries + testIndex;
		test = entry->createFcn();
		viewZoom = 1.0f;
		settings.viewCenter.Set(0.0f, 20.0f);
		updateView();
	}
}

void drawControls(DebugRenderer& renderer)
{	
	const char* strings[] = {
		"Press 'i'/'o' to zoom in/out",
		"Press 'v' to reset the camera",
		"Use arrows to move",
		"",
		"Press 'r' to reset test",
		"Press 'w'/'x' to go to previous/next test",
		"Press SHIFT + LEFT CLICK to launch a bomb",
		"Press 'p' to toggle pause mode",
		"",
		"Press 'h' to toggle help display"
	};
	const unsigned int stringCount = sizeof(strings)/sizeof(const char*);
	const unsigned int h = window->getSize().y, step = 15;
	const unsigned int start = h - step*(stringCount) - 5;

	struct drawingOptions {
		const char* str;
		bool active;
	} drawingOptionStrings[] = {
		{"Press 't' to toggle shapes drawing", settings.drawShapes},
		{"Press 'y' to toggle joints drawing", settings.drawJoints},
		{"Press 'u' to toggle AABBs drawing", settings.drawAABBs},
		{"", true},
		{"Press 'j' to toggle contact points drawing", settings.drawContactPoints},
		{"Press 'k' to toggle contact normals drawing", settings.drawContactNormals},
		{"Press 'l' to toggle contact impulses drawing", settings.drawContactForces},
		{"Press 'm' to toggle friction impulses drawing", settings.drawFrictionForces},
		{"", true},
		{"Press 'q' to toggle pairs drawing", settings.drawPairs},
		{"Press 's' to toggle centers of mass drawing", settings.drawCOMs},
		{"Press 'd' to toggle statistics drawing", settings.drawStats},
		{"Press 'f' to toggle profile drawing", settings.drawProfile},
		{"", true},
		{"Press 'c' to enable/disable warm starting", settings.enableWarmStarting},
		{"Press 'b' to enable/disable continuous physics", settings.enableContinuous},
		{"Press 'n' to enable/disable substepping", settings.enableSubStepping}
	};
	const unsigned int optionCount = sizeof(drawingOptionStrings)/sizeof(struct drawingOptions);
	const unsigned int optionStart = start - step*(optionCount+1);
	const b2Color trueColor(0., 1., 0.), falseColor(1., 0., 0.);

	if (displayControls)
	{
		for (unsigned int i=0; i<stringCount; i++)
			renderer.DrawString(5, start + i*step, strings[i]);
		for (unsigned int i=0; i<optionCount; i++)
		{
			struct drawingOptions opt = drawingOptionStrings[i];
			b2Color color = (opt.active) ? trueColor : falseColor;

			renderer.DrawString(5, optionStart + i*step, color, opt.str);
		}
	}
	else
		renderer.DrawString(5, h - step - 5, strings[stringCount-1]);
}

bool keyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Escape:
			return false;
		// Press 'i' to zoom in.
		case sf::Keyboard::I:
			viewZoom = b2Max(0.9f * viewZoom, 0.02f);
			updateView(false);
			break;
		// Press 'o' to zoom out.
		case sf::Keyboard::O:
			viewZoom = b2Min(1.1f * viewZoom, 20.0f);
			updateView(false);
			break;

		// Arrow keys to move view
		case sf::Keyboard::Up:
			viewCenter.y -= 0.05 * viewZoom * viewSize.y;
			updateView(false);
			break;
		case sf::Keyboard::Down:
			viewCenter.y += 0.05 * viewZoom * viewSize.y;
			updateView(false);
			break;
		case sf::Keyboard::Left:
			viewCenter.x -= 0.05 * viewZoom * viewSize.x;
			updateView(false);
			break;
		case sf::Keyboard::Right:
			viewCenter.x += 0.05 * viewZoom * viewSize.x;
			updateView(false);
			break;

		// Press 'r' to reset.
		case sf::Keyboard::R:
			delete test;
			test = entry->createFcn();
			updateView();
		break;

		// Press space to launch a bomb.
		case ' ':
			if (test)
				test->LaunchBomb();
			break;
		case sf::Keyboard::P:
			settings.pause = !settings.pause;
			break;
		case sf::Keyboard::W:
			--testSelection;
			if (testSelection < 0)
				testSelection = testCount - 1;
			break;
		case sf::Keyboard::X:
			++testSelection;
			if (testSelection >= testCount)
				testSelection = 0;
			break;
		case sf::Keyboard::V:
			updateView();
			break;
		case sf::Keyboard::H:
			displayControls = !displayControls;
			break;

		// Display options
		case sf::Keyboard::T:
			settings.drawShapes = !settings.drawShapes;
			break;
		case sf::Keyboard::Y:
			settings.drawJoints = !settings.drawJoints;
			break;
		case sf::Keyboard::U:
			settings.drawAABBs = !settings.drawAABBs;
			break;

		case sf::Keyboard::J:
			settings.drawContactPoints = !settings.drawContactPoints;
			break;
		case sf::Keyboard::K:
			settings.drawContactNormals = !settings.drawContactNormals;
			break;
		case sf::Keyboard::L:
			settings.drawContactForces = !settings.drawContactForces;
			break;
		case sf::Keyboard::M:
			settings.drawFrictionForces = !settings.drawFrictionForces;
			break;
			
		case sf::Keyboard::Q:
			settings.drawPairs = !settings.drawPairs;
			break;
		case sf::Keyboard::S:
			settings.drawCOMs = !settings.drawCOMs;
			break;
		case sf::Keyboard::D:
			settings.drawStats = !settings.drawStats;
			break;
		case sf::Keyboard::F:
			settings.drawProfile = !settings.drawProfile;
			break;
		case sf::Keyboard::C:
			settings.enableWarmStarting = !settings.enableWarmStarting;
			break;
		case sf::Keyboard::B:
			settings.enableContinuous = !settings.enableContinuous;
			break;
		case sf::Keyboard::N:
			settings.enableSubStepping = !settings.enableSubStepping;
			break;
		default:
			break;
	}
	
	char c = key2char(key);
	if (test && c)
		test->Keyboard(c);

	return true;
}

bool keyReleased(sf::Keyboard::Key key)
{
	unsigned char c = key2char(key);

	if (test && c)
		test->KeyboardUp(c);

	return true;
}

void mousePressed(sf::Mouse::Button button, int x, int y)
{
	b2Vec2 p = ConvertScreenToWorld(x, y);

	switch (button)
	{
		case sf::Mouse::Left:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				if (test)
					test->ShiftMouseDown(p);
			}
			else
				if (test)
					test->MouseDown(p);
			break;

		case sf::Mouse::Right:
			lastp = sfConvertScreenToWorld(x, y);
			rMouseDown = true;
			break;

		default:
			break;
	}
}

void mouseReleased(sf::Mouse::Button button, int x, int y)
{
	b2Vec2 p = ConvertScreenToWorld(x, y);

	switch (button)
	{
		case sf::Mouse::Left:
			if (test)
				test->MouseUp(p);
			break;

		case sf::Mouse::Right:
			rMouseDown = false;
			break;

		default:
			break;
	}
}

void mouseMotion(int x, int y)
{
	sf::Vector2f p = sfConvertScreenToWorld(x, y);

	if (test)
		test->MouseMove(b2Vec2(p.x, p.y));
	
	if (rMouseDown)
	{
		sf::Vector2f diff = lastp - p;
		viewCenter += diff;

		/*
		std::cout << x << " " << y << std::endl;
		std::cout << p.x << " " << p.y << std::endl;
		std::cout << lastp.x << " " << lastp.y << std::endl;
		std::cout << diff.x << " " << diff.y << std::endl;
		std::cout << std::endl;
		updateView(false);
		//*/
		lastp = p;
	}
}

