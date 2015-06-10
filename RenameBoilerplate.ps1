#!Пока что не понял почему, но скрипт надо выполнить два раза, чтобы переименовались файлы во вложенных папках.

#Перед запуском этого скрипта каталог с проектом нужно переименовать с BoilerplateName на новое название ProjectName.
#Скрипт осуществляет замену BoilerplateName на ProjectName в названиях и в тексте всех файлов (помимо этого скрипта).
#После работы скрипта (но не ранее!) Soulution ProjectName.sln можно открывать в VS2013 и собирать.
#Названия всех проектов и связанных сущностей в VS будут соответствовать ProjectName.

$BoilerplateName = 'CppBoilerplateVS2013GtestGmockDoxygen'
$ThisScriptName = 'RenameBoilerplate.ps1'
$ProjectName = (Get-ItemProperty $ThisScriptName).Directory.Name

#Переименовываем файлы и папки
Dir -Filter "$($BoilerPlateName)*" -Recurse | Rename-Item  -NewName { $_.name -replace $BoilerPlateName, $ProjectName }

#Осуществляем замену в текстах файлов
$files=Dir -Exclude $ThisScriptName -Recurse
foreach ($file in $files) 
{
    if (!$file.PSIsContainer) { #не пытаемся сделать замену в тексте папки
        (Get-Content $file.PSPath) | 
        Foreach-Object {$_ -replace $BoilerPlateName, $ProjectName} |
        Set-Content $file.PSPath
    }
}