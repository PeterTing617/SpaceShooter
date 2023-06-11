#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* f, string txt, Color textIdle, Color textHover, Color textActive, Color idleC, Color hoverC, Color activeC, int size, Color outline, float outlinethickness)
{
	buttonState = BTN_IDLE;

	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	shape.setFillColor(idleC);

	font = f;
	text.setFont(*font);
	text.setString(txt);
	text.setFillColor(textIdle);
	text.setCharacterSize(size);
	text.setOutlineColor(outline);
	text.setOutlineThickness(outlinethickness);
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f, shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);

	txtIdleColor = textIdle;
	txtHoverColor = textHover;
	txtActiveColor = textActive;

	idleColor = idleC;
	hoverColor = hoverC;
	activeColor = activeC;
}

Button::~Button()
{
}

bool Button::isPressed()
{
	if (buttonState == BTN_ACTIVE) {
		return true;
	}
	else {
		return false;
	}
}

void Button::update(const Vector2f& mousePos)
{
	buttonState = BTN_IDLE;
	// Update bool for hover and pressed
	if (shape.getGlobalBounds().contains(mousePos)) {
		buttonState = BTN_HOVER;

		if (Mouse::isButtonPressed(Mouse::Left)) {
			buttonState = BTN_ACTIVE;
		}
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(txtIdleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(txtHoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(txtActiveColor);
		break;

	default:
		shape.setFillColor(Color::Red);
		text.setFillColor(Color::Blue);
		break;
	}
}

void Button::render(RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
