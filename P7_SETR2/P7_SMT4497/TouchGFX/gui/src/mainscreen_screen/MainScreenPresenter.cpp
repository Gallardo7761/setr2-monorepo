#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::set_button(bool state)
{
	view.set_button(state); // actualiza la view (UI)
}

void MainScreenPresenter::set_temperature(uint16_t temp)
{
	view.set_temperature(temp); // actualiza la view (UI)
}

