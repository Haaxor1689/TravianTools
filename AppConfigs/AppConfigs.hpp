#ifndef APPCONFIGS_HPP
#define APPCONFIGS_HPP

#include <QString>
#include <QVector>
#include <QDebug>

#include "Other/json.hpp"
#include "Other/PixmapSheet.hpp"
#include "Macros.hpp"

GroupStart(StyleSheet)
AddConst(QString, normal,
    "QWidget { background: grey; }"
    "QPushButton { background-color: green; }")
GroupEnd

GroupStart(Defaults)
Add(QString, privateApiKey, "")
Add(QString, publicSiteKey, "")
Add(QString, server, "")
AddConst(int, cellWidth, 126)
AddConst(int, cellHeight, 68)
AddConst(int, cellOverlayHeight, 84)
Add(PixmapSheet, mapSheet, [](){
	    PixmapSheet sheet(":/map.png");
		sheet.addKey("grass", { 252, 1408, cellWidth(), cellHeight() });
		// Fields
		sheet.addKey("0", { 126, 1408, cellWidth(), cellHeight() });
		sheet.addKey("1", { 378, 1408, cellWidth(), cellHeight() });
		sheet.addKey("2", { 1508, 204, cellWidth(), cellHeight() });
		sheet.addKey("3", { 1508, 952, cellWidth(), cellHeight() });
		sheet.addKey("4", { 1508, 1156, cellWidth(), cellHeight() });
		sheet.addKey("5", { 1508, 1224, cellWidth(), cellHeight() });
		sheet.addKey("6", { 1508, 0, cellWidth(), cellHeight() });
		sheet.addKey("7", { 1508, 1360, cellWidth(), cellHeight() });
		sheet.addKey("8", { 1634, 204, cellWidth(), cellHeight() });
		sheet.addKey("9", { 1634, 272, cellWidth(), cellHeight() });
		sheet.addKey("10", { 604, 1408, cellWidth(), cellHeight() });
		sheet.addKey("11", { 630, 1408, cellWidth(), cellHeight() });
		sheet.addKey("12", { 756, 1408, cellWidth(), cellHeight() });
		sheet.addKey("13", { 882, 1408, cellWidth(), cellHeight() });
		sheet.addKey("14", { 1008, 1408, cellWidth(), cellHeight() });
		sheet.addKey("15", { 1134, 1408, cellWidth(), cellHeight() });
		// Wood
		sheet.addKey("1055", { 252, 420, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1145", { 630, 504, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1155", { 0, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1165", { 126, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1255", { 252, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1256", { 378, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1265", { 504, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1354", { 630, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1355", { 0, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1364", { 126, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1365", { 252, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1454", { 378, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1455", { 504, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1465", { 630, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1555", { 756, 0, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1655", { 756, 84, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1755", { 756, 168, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1756", { 756, 252, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1764", { 756, 336, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1765", { 756, 420, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1766", { 756, 504, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1855", { 756, 588, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1856", { 756, 672, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1864", { 0, 756, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1865", { 126, 756, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1955", { 252, 756, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1956", { 378, 756, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1964", { 504, 756, cellWidth(), cellOverlayHeight() });
		sheet.addKey("1965", { 126, 0, cellWidth(), cellOverlayHeight() });
		// Clay
		sheet.addKey("2055", { 882, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2155", { 1008, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2255", { 1134, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2355", { 1260, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2455", { 1386, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2555", { 1512, 1612, cellWidth(), cellHeight() });
		sheet.addKey("2655", { 0, 1680, cellWidth(), cellHeight() });
		sheet.addKey("2656", { 126, 1680, cellWidth(), cellHeight() });
		sheet.addKey("2665", { 252, 1680, cellWidth(), cellHeight() });
		sheet.addKey("2755", { 882, 1680, cellWidth(), cellHeight() });
		sheet.addKey("2756", { 1008, 1680, cellWidth(), cellHeight() });
		sheet.addKey("2765", { 1134, 1680, cellWidth(), cellHeight() });
		// Iron
		sheet.addKey("3055", { 504, 504, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3155", { 0, 168, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3156", { 126, 168, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3255", { 252, 0, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3265", { 252, 84, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3355", { 252, 168, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3365", { 0, 252, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3366", { 126, 252, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3455", { 252, 252, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3555", { 378, 0, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3655", { 378, 84, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3755", { 378, 168, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3756", { 378, 252, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3855", { 0, 336, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3865", { 126, 336, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3955", { 252, 336, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3965", { 378, 336, cellWidth(), cellOverlayHeight() });
		sheet.addKey("3966", { 0, 420, cellWidth(), cellOverlayHeight() });
		// Crop
		sheet.addKey("4055", { 1260, 1680, cellWidth(), cellHeight() });
		sheet.addKey("4145", { 1760, 68, cellWidth(), cellHeight() });
		sheet.addKey("4155", { 1760, 136, cellWidth(), cellHeight() });
		sheet.addKey("4255", { 1382, 1020, cellWidth(), cellHeight() });
		sheet.addKey("4256", { 1382, 1088, cellWidth(), cellHeight() });
		sheet.addKey("4265", { 1382, 1156, cellWidth(), cellHeight() });
		sheet.addKey("4355", { 1382, 1224, cellWidth(), cellHeight() });
		sheet.addKey("4455", { 0, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4555", { 126, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4655", { 252, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4745", { 378, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4755", { 504, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4845", { 630, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4855", { 756, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4955", { 882, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4956", { 1008, 1340, cellWidth(), cellHeight() });
		sheet.addKey("4965", { 1134, 1340, cellWidth(), cellHeight() });
		// World wonder
		sheet.addKey("9000", { 756, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9001", { 630, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9002", { 882, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9003", { 1008, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9004", { 1134, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9010", { 126, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9011", { 0, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9012", { 252, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9013", { 378, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9014", { 504, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9020", { 1386, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9021", { 1260, 1476, cellWidth(), cellHeight() });
		sheet.addKey("9022", { 0, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9023", { 126, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9024", { 252, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9030", { 504, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9031", { 378, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9032", { 630, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9033", { 756, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9034", { 882, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9040", { 1134, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9041", { 1008, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9042", { 1260, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9043", { 1386, 1544, cellWidth(), cellHeight() });
		sheet.addKey("9044", { 1634, 0, cellWidth(), cellHeight() });
		// Oasis markers
		sheet.addKey("o10", { 1568, 1432, 20, 19 });
		sheet.addKey("o11", { 1537, 1429, 26, 26 });
		sheet.addKey("o20", { 1512, 1432, 20, 19 });
		sheet.addKey("o21", { 1411, 1293, 27, 26 });
		sheet.addKey("o30", { 1695, 1569, 20, 17 });
		sheet.addKey("o31", { 1383, 1293, 26, 26 });
		sheet.addKey("o40", { 1596, 1432, 20, 20 });
		sheet.addKey("o41", { 1720, 1565, 26, 26 });
		// Villages
		sheet.addKey("romanTiny", { 1760, 1224, cellWidth(), cellHeight() });
		sheet.addKey("romanSmall", { 1760, 1360, cellWidth(), cellHeight() });
		sheet.addKey("romanMedium", { 1760, 1496, cellWidth(), cellHeight() });
		sheet.addKey("romanBig", { 1760, 1632, cellWidth(), cellHeight() });
		sheet.addKey("romanHuge", { 126, 1748, cellWidth(), cellHeight() });
		sheet.addKey("romanCity", { 378, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonTiny", { 630, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonSmall", { 882, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonMedium", { 1134, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonBig", { 1386, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonHuge", { 1638, 1748, cellWidth(), cellHeight() });
		sheet.addKey("teutonCity", { 126, 1816, cellWidth(), cellHeight() });
		sheet.addKey("gaulTiny", { 378, 1816, cellWidth(), cellHeight() });
		sheet.addKey("gaulSmall", { 756, 756, cellWidth(), cellHeight() });
		sheet.addKey("gaulMedium", { 926, 1240, cellWidth(), cellHeight() });
		sheet.addKey("gaulBig", { 1178, 1240, cellWidth(), cellHeight() });
		sheet.addKey("gaulHuge", { 1382, 68, cellWidth(), cellHeight() });
		sheet.addKey("gaulCity", { 1382, 204, cellWidth(), cellHeight() });

		return sheet;
        }())
GroupEnd

class Utilities {
public:
	static int getInt(const nlohmann::json& json) {
		return json.is_string() ? std::stoi(json.get<std::string>()) : json.get<int>();
	}

private:
	Utilities() {}
};

#endif // APPCONFIGS_HPP
