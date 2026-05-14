# Система управления пользователями
Реализуйте классы User и Group. Класс User должен содержать информацию, такую как имя пользователя, уникальный идентификатор и другие релевантные данные (на ваше усмотрение), а также содержать ссылку на группу, в которой состоит пользователь (пользователь может и не состоять в группе). Класс Group должен содержать идентификатор группы и список всех пользователей, которые в ней состоят. Между классами User и Group не должно быть циклических зависимостей!

Создайте консольную утилиту для управления пользователями и группами пользователей, которая должна поддерживать следующие команды:

● createUser {userId} {username} {…дополнительная информация…} – создание нового пользователя;
● deleteUser {userId} – удаление пользователя;
● allUsers – вывод информации по всем пользователям;
● getUser {userId} – вывести информацию по одному пользователю;
● createGroup {groupId} – создать новую группу;
● deleteGroup {groupId} – удалить группу;
● allGroups – вывеси информацию по всем группам, включая всех пользователей, которые в них состоят;
● getGroup {groupId} – вывести информацию по одной группе, включая всех пользователей, которые в ней состоят.



## Демонстрация работы
> g++ -std=c++17 main.cpp user.cpp group.cpp user_manager.cpp -o user_manager  
> ./user_manager  


createUser 1 harry_potter OrderOfThePhoenix "Harry James Potter" Stag "Holly, 11'', phoenix feather"
createUser 2 hermione_granger OrderOfThePhoenix "Hermione Jean Granger" Otter "Vinewood, 10¾'', dragon heartstring"
createUser 3 ron_weasley OrderOfThePhoenix "Ronald Bilius Weasley" JackRussellTerrier "Ash, 12'', unicorn hair"
createUser 4 albus_dumbledore OrderOfThePhoenix "Albus Percival Wulfric Brian Dumbledore" Phoenix "Elder, 15'', Thestral tail hair"
createUser 5 severus_snape OrderOfThePhoenix "Severus Snape" Doe "Unknown"
createUser 6 minerva_mcgonagall OrderOfThePhoenix "Minerva McGonagall" Cat "Fir, 9'', dragon heartstring"
createUser 7 sirius_black OrderOfThePhoenix "Sirius Black" Dog "Unknown"
createUser 8 remus_lupin OrderOfThePhoenix "Remus Lupin" Wolf "Unknown"
createUser 9 voldemort DeathEaters "Tom Marvolo Riddle" "" "Yew, 13½'', phoenix feather"
createUser 10 bellatrix DeathEaters "Bellatrix Lestrange" "" "Walnut, 12¾'', dragon heartstring"
createUser 11 lucius_malfoy DeathEaters "Lucius Malfoy" "" "Elm, 12'', dragon heartstring"
createUser 12 draco_malfoy DeathEaters "Draco Lucius Malfoy" "" "Hawthorn, 10'', unicorn hair"
createUser 13 pettigrew DeathEaters "Peter Pettigrew" "" "Unknown"
createUser 14 yaxley DeathEaters "Corban Yaxley" "" "Unknown"
createGroup OrderOfThePhoenix
createGroup DeathEaters
addUserToGroup 1 OrderOfThePhoenix
addUserToGroup 2 OrderOfThePhoenix
addUserToGroup 3 OrderOfThePhoenix
addUserToGroup 4 OrderOfThePhoenix
addUserToGroup 5 OrderOfThePhoenix
addUserToGroup 6 OrderOfThePhoenix
addUserToGroup 7 OrderOfThePhoenix
addUserToGroup 8 OrderOfThePhoenix
addUserToGroup 9 DeathEaters
addUserToGroup 10 DeathEaters
addUserToGroup 11 DeathEaters
addUserToGroup 12 DeathEaters
addUserToGroup 13 DeathEaters
addUserToGroup 14 DeathEaters
allGroups
allUsers
getGroup OrderOfThePhoenix
