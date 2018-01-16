#pragma once
char **phrases = new char*[19];
void seteng()
{
	phrases[0] = "Saper\n";
	phrases[1] = "Set size x:";
	phrases[2] = "Set size y:";
	phrases[3] = "Set number of mines:";
	phrases[4] = "Set normal number of mines";
	phrases[5] = "1. Make step\n";
	phrases[6] = "2. Set flag\n";
	phrases[7] = "3. Take off flag\n";
	phrases[8] = "Set coordinates through a space(x y):";
	phrases[9] = "Choose one variant:\n";
	phrases[10] = "You have won!\n";
	phrases[11] = "Time:";
	phrases[12] = " sec.\n";
	phrases[13] = "New best record in playing on this square and with this number of mines.\n";
	phrases[14] = "Best record on this square and with this number of mines:";
	phrases[15] = "Set normal coordinates.\n";
	phrases[16] = "You have lose.\n";
	phrases[17] = "On the field there are already masimum number of flags.\n";
	phrases[18] = "This dot is already opened.\n";
}

void setrus()
{
	phrases[0] = "Сапер\n";
	phrases[1] = "Укажите размер x:";
	phrases[2] = "Укажите размер y:";
	phrases[3] = "Укажите количество мин:";
	phrases[4] = "Укажите нормальное количество мин:";
	phrases[5] = "1. Сходить\n";
	phrases[6] = "2. Поставить флаг\n";
	phrases[7] = "3. Снять флаг\n";
	phrases[8] = "Введите координаты через пробел(x y):";
	phrases[9] = "Выберите один из вариантов:\n";
	phrases[10] = "Вы выйграли!\n";
	phrases[11] = "Время:";
	phrases[12] = " сек.\n";
	phrases[13] = "Новый рекорд прохождения на этой площади и с этим количествоим мин.\n";
	phrases[14] = "Рекорд на этой площади и с этим количествоим мин:";
	phrases[15] = "Введите нормальные координаты.\n";
	phrases[16] = "Вы проиграли.\n";
	phrases[17] = "На карте уже стоит максимальное количество флагов.\n";
	phrases[18] = "Эта точка уже открыта.\n";
}