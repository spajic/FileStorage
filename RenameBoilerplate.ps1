#!���� ��� �� ����� ������, �� ������ ���� ��������� ��� ����, ����� ��������������� ����� �� ��������� ������.

#����� �������� ����� ������� ������� � �������� ����� ������������� � BoilerplateName �� ����� �������� ProjectName.
#������ ������������ ������ BoilerplateName �� ProjectName � ��������� � � ������ ���� ������ (������ ����� �������).
#����� ������ ������� (�� �� �����!) Soulution ProjectName.sln ����� ��������� � VS2013 � ��������.
#�������� ���� �������� � ��������� ��������� � VS ����� ��������������� ProjectName.

$BoilerplateName = 'CppBoilerplateVS2013GtestGmockDoxygen'
$ThisScriptName = 'RenameBoilerplate.ps1'
$ProjectName = (Get-ItemProperty $ThisScriptName).Directory.Name

#��������������� ����� � �����
Dir -Filter "$($BoilerPlateName)*" -Recurse | Rename-Item  -NewName { $_.name -replace $BoilerPlateName, $ProjectName }

#������������ ������ � ������� ������
$files=Dir -Exclude $ThisScriptName -Recurse
foreach ($file in $files) 
{
    if (!$file.PSIsContainer) { #�� �������� ������� ������ � ������ �����
        (Get-Content $file.PSPath) | 
        Foreach-Object {$_ -replace $BoilerPlateName, $ProjectName} |
        Set-Content $file.PSPath
    }
}