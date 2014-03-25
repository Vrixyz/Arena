#include "LayerHud.h"

/// Please set the view in which you want your layer to be displayed later
LayerHud::LayerHud(sf::RenderTarget* r) : Drawable(), Transformable(),
	view(r->getView()), s_health()
{
}


LayerHud::~LayerHud(void)
{
}

void LayerHud::draw( sf::RenderTarget& r, sf::RenderStates states) const
{
	states.transform *= getTransform();
	const sf::View updatedView;
	

	r.setView(view);
	s_health.draw(r, states);
	// draw
	// reset the view
	
}

void LayerHud::draw()
{

}
