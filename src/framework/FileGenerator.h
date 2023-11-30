#pragma once

class FileGenerator
{
	void CreateTemplate(int day);
	void CreateDefinitionFile(int day, int part);
	void CreateImplementationFile(int day, int part);
	void CreateInputFile(int day, int part, bool isExample);
	void RegisterSourceFile();
};
