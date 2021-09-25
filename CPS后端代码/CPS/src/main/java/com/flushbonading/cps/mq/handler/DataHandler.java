package com.flushbonading.cps.mq.handler;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.flushbonading.cps.constant.MachineData;
import com.flushbonading.cps.entity.Equipment;
import com.flushbonading.cps.entity.dto.AddProductDTO;
import com.flushbonading.cps.entity.dto.AddRecordDTO;
import com.flushbonading.cps.entity.dto.DeviceParametersDTO;
import com.flushbonading.cps.entity.vo.BrandVO;
import com.flushbonading.cps.entity.vo.EnvironmentVO;
import com.flushbonading.cps.entity.vo.PanelDataVO;
import com.flushbonading.cps.mapper.*;
import com.flushbonading.cps.service.*;
import com.flushbonading.cps.util.OKHttpUtil;
import com.flushbonading.cps.util.RemarkUtil;
import com.flushbonading.cps.util.TimeQuantumUtil;
import com.flushbonading.cps.websocket.WebSocket;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.List;

/**
 * @author zyx 2134208960@qq.com
 * @date 2021/6/22 20:55
 * @since 1.0.0
 */
@Component
@Slf4j
public class DataHandler {

    @Autowired
    WebSocket webSocket;

    @Autowired
    private OKHttpUtil okHttpUtil;
    @Autowired
    private ProductMapper productMapper;
    @Autowired
    private DeviceParametersMapper deviceParametersMapper;
    @Autowired
    private EnvironmentMapper environmentMapper;
    @Autowired
    private EnvironmentService environmentService;
    @Autowired
    private MaintenanceRecordMapper maintenanceRecordMapper;
    @Autowired
    private EquipmentMapper equipmentMapper;
    @Autowired
    private StaffDeviceMapper staffDeviceMapper;
    @Autowired
    private DiaryMapper diaryMapper;

    @Autowired
    EquipmentService equipmentService;
    @Autowired
    DiaryService diaryService;
    @Autowired
    ProductService productService;
    @Autowired
    MaterialService materialService;

    public void parseData(Long msgId, String data) {
        JSONObject jsonObect = JSON.parseObject(data);
        String body = jsonObect.getString("body");
        System.out.println(body);
        String[] array = body.split(",");
        log.info("======接收到数据:" + array);
        switch (array[0]) {
            case MachineData.PRODUCT_MESSAGE:
                productHandler(array);
                break;
            case MachineData.ENVIRONMENT_MESSAGE:
                environmentHandler(array);
                break;
            case MachineData.MAINTAIN_MESSAGE:
                maintainHandler(array);
                break;
            default:
                break;
        }

        List<String> brandName = materialService.getBrandName();
        List<String> brandData = productService.getBrandData(brandName);
        BrandVO brand = BrandVO.builder()
                .brandName(brandName)
                .brandData(brandData)
                .build();
        PanelDataVO panelData = PanelDataVO.builder()
                .environmentData(environmentService.getNowEnvironmentVO())
                .diaryData(diaryService.getDiaryDataVos())
                .brand(brand)
                .yieldData(productService.getYieldData())
                .maintenanceData(equipmentService.getMaintenanceDataVO())
                .defectiveData(productService.getDefectiveData())
                .build();

        webSocket.sendMessage(JSON.toJSONString(panelData));
    }

    /**
     * 生产数据处理
     *
     * @param data
     */
    public void productHandler(String[] data) {
        //解析数据
        //设备编号
        String equipmentId = data[1];
        //产品Id
        String productId = data[2];
        //包装人员
        String packingWorker = data[3];
        //压型人员
        String producer = data[4];
        //模具号
        String modelNumber = data[5];
        //称粉时间
        String saidPowderTime = data[7];
        //压制压力
        String pressingPressure = data[8];
        //保压压力
        String dwelPressure = data[9];
        //重量
        String weight = data[10];
        //尺寸
        String size = data[11];
        //退磁电流
        String currentDemagnetization = data[12];
        //充磁电流
        String currentMagnetization = data[13];
        //物料Id
        String materialId = data[14];
        //产品结果
        String resultId = data[15];

        //将数据传给CPS得到对应的结果


        //下发结果
//        String[] dataRelease = new String[1];
//        dataRelease[0] = "R,0";
//        okHttpUtil.postData(dataRelease);
//        dataRelease[0] = "0";
//        RestTemplate restTemplate = new RestTemplate();
//        restTemplate.postForObject("http://localhost:8087/cps/dataReleased/post", dataRelease, String.class);
        if (materialId.equals("0")) {
            materialId = "35EH";
        }
        /*
            dairy表加1
         */

        //将对应的设备的数量加1
        QueryWrapper<Equipment> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("equipment_id", equipmentId);
        Equipment equipment = equipmentMapper.selectOne(queryWrapper);
        System.out.println(equipmentId);
        if (equipment != null) {
            /*插入一条产品数据*/
            log.info("插入了一条产品数据");
            AddProductDTO build = AddProductDTO.builder()
                    .currentDemagnetization(currentDemagnetization)
                    .currentMagnetization(currentMagnetization)
                    .dwellPressure(dwelPressure)
                    .equipmentId(equipmentId)
                    .materialId(materialId)
                    .modelNumber(modelNumber)
                    .packagingWorker(packingWorker)
                    .pressingPressure(pressingPressure)
                    .producer(producer)
                    .productNumber(productId)
                    .size(size)
                    .saidPowderTime(saidPowderTime)
                    .result(resultId)
                    .build();

            System.out.println("产品结果:" + resultId);
            //System.out.println(build);
            //System.out.println(productMapper);
            productMapper.insertAProduct(build);

            Calendar calendar = Calendar.getInstance();
            int hour = calendar.get(Calendar.HOUR_OF_DAY);
            TimeQuantumUtil quantumUtil = TimeQuantumUtil.getInstance();
            String time = quantumUtil.time(hour);
            System.out.println(TimeQuantumUtil.getInstance().time(hour));
            diaryMapper.increase(equipmentId, TimeQuantumUtil.getInstance().time(hour));
            //修改并插入一条设备参数信息
            //deviceParametersMapper.updateDeviceParameters(equipmentId);
            DeviceParametersDTO parametersDTO = DeviceParametersDTO.builder()
                    .currentDemagnetization(currentDemagnetization)
                    .currentMagnetization(currentMagnetization)
                    .dwellPressure(dwelPressure)
                    .equipmentId(equipmentId)
                    .pressingPressure(pressingPressure)
                    .build();
            deviceParametersMapper.updateDeviceParameters(equipmentId);
            deviceParametersMapper.insertDeviceParameters(parametersDTO);

            if (!packingWorker.equals(equipment.getPackagingWorker()) || !producer.equals(equipment.getProducer())) {
                //更改设备工作的人员信息
                equipmentMapper.updatePeople(equipmentId, packingWorker, producer);
                //将数据插入到员工设备表
                System.out.println("插入了员工设备表");
                staffDeviceMapper.insertAStaffDevice(equipmentId, packingWorker, producer);
            }
            equipmentMapper.increase(equipmentId);

            //得到当前时间

            //将对应的的员工设备表的数量加1
            staffDeviceMapper.increase(equipmentId, packingWorker, producer);
        }

    }

    /**
     * 环境数据处理
     *
     * @param data
     */
    public void environmentHandler(String[] data) {
        //粉尘浓度
        String dust = data[1];
        //温度
        String temperature = data[2];
        //湿度
        String humidity = data[3].substring(0, data[3].length() - 1);

        EnvironmentVO environmentVO = EnvironmentVO.builder()
                .dust(dust)
                .humidity(humidity)
                .temperature(temperature)
                .build();


        //修改环境信息
        environmentMapper.updateEnvironment(dust, humidity, temperature);

        //webSocket.sendMessage(JSON.toJSONString(environmentService.queryEnvironmentMessage()));
    }

    /**
     * 保养数据处理
     *
     * @param data
     */
    public void maintainHandler(String[] data) {
        //设备号
        String equipmentId = data[1];
        //保养人姓名
        String name = data[2];
        //保养内容
        String remarkId = data[4];
        //保养时间
        String createTime = data[3];
        //修改保养日期
        String maintenancePeriod = data[5];
        createTime = "20" + createTime;
        StringBuffer stringBuffer = new StringBuffer(createTime);
        StringBuffer insert = stringBuffer.insert(5, '0');
        createTime = insert.toString();
        String[] split = createTime.split(":");
        if (split[1].length() < 2) {
            StringBuffer buffer = new StringBuffer(createTime);
            createTime = buffer.insert(14, "0").toString();
        }
        createTime = createTime.substring(0, 16);
        //对时间进行一些处理
        Calendar calendar = Calendar.getInstance();
        calendar.get(Calendar.SECOND);
        SimpleDateFormat s = new SimpleDateFormat("ss");
        String second = s.format(calendar.getTime());

        createTime = createTime + ":" + second;
        //System.out.println(createTime);
        maintenancePeriod = maintenancePeriod + ":" + second;
        String remark = RemarkUtil.getInstance().remark(remarkId);
        //增加一条保养记录
        AddRecordDTO addRecord = AddRecordDTO.builder()
                .createTime(createTime)
                .equipmentId(equipmentId)
                .name(name)
                .remark(remark)
                .build();
        maintenanceRecordMapper.addAMaintenanceRecord(addRecord);

        //修改设备下次保养时间
        equipmentMapper.updateMaintenancePeriod(maintenancePeriod, equipmentId);
        okHttpUtil.postData("M,1,0,N");

    }
}
