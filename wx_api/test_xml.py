import xml.etree.ElementTree as ET

tree = ET.parse('account.xml')
root = tree.getroot()
appid = root.find('mchid')
if appid is not None:
    print appid.text
else:
    print 'null'


