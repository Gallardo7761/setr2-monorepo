#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    MainScreenViewBase::setupScreen();
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::set_button(bool state)
{
	led_on.setVisible(state);
	led_on.invalidate();
}

void MainScreenView::set_temperature(uint16_t temp)
{
	temperature.setValue(temp);
	temperature.invalidate();
}
