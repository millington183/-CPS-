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
        log.info("======???????????????:" + array);
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
     * ??????????????????
     *
     * @param data
     */
    public void productHandler(String[] data) {
        //????????????
        //????????????
        String equipmentId = data[1];
        //??????Id
        String productId = data[2];
        //????????????
        String packingWorker = data[3];
        //????????????
        String producer = data[4];
        //?????????
        String modelNumber = data[5];
        //????????????
        String saidPowderTime = data[7];
        //????????????
        String pressingPressure = data[8];
        //????????????
        String dwelPressure = data[9];
        //??????
        String weight = data[10];
        //??????
        String size = data[11];
        //????????????
        String currentDemagnetization = data[12];
        //????????????
        String currentMagnetization = data[13];
        //??????Id
        String materialId = data[14];
        //????????????
        String resultId = data[15];

        //???????????????CPS?????????????????????


        //????????????
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
            dairy??????1
         */

        //??????????????????????????????1
        QueryWrapper<Equipment> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("equipment_id", equipmentId);
        Equipment equipment = equipmentMapper.selectOne(queryWrapper);
        System.out.println(equipmentId);
        if (equipment != null) {
            /*????????????????????????*/
            log.info("???????????????????????????");
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

            System.out.println("????????????:" + resultId);
            //System.out.println(build);
            //System.out.println(productMapper);
            productMapper.insertAProduct(build);

            Calendar calendar = Calendar.getInstance();
            int hour = calendar.get(Calendar.HOUR_OF_DAY);
            TimeQuantumUtil quantumUtil = TimeQuantumUtil.getInstance();
            String time = quantumUtil.time(hour);
            System.out.println(TimeQuantumUtil.getInstance().time(hour));
            diaryMapper.increase(equipmentId, TimeQuantumUtil.getInstance().time(hour));
            //???????????????????????????????????????
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
                //?????????????????????????????????
                equipmentMapper.updatePeople(equipmentId, packingWorker, producer);
                //?????????????????????????????????
                System.out.println("????????????????????????");
                staffDeviceMapper.insertAStaffDevice(equipmentId, packingWorker, producer);
            }
            equipmentMapper.increase(equipmentId);

            //??????????????????

            //??????????????????????????????????????????1
            staffDeviceMapper.increase(equipmentId, packingWorker, producer);
        }

    }

    /**
     * ??????????????????
     *
     * @param data
     */
    public void environmentHandler(String[] data) {
        //????????????
        String dust = data[1];
        //??????
        String temperature = data[2];
        //??????
        String humidity = data[3].substring(0, data[3].length() - 1);

        EnvironmentVO environmentVO = EnvironmentVO.builder()
                .dust(dust)
                .humidity(humidity)
                .temperature(temperature)
                .build();


        //??????????????????
        environmentMapper.updateEnvironment(dust, humidity, temperature);

        //webSocket.sendMessage(JSON.toJSONString(environmentService.queryEnvironmentMessage()));
    }

    /**
     * ??????????????????
     *
     * @param data
     */
    public void maintainHandler(String[] data) {
        //?????????
        String equipmentId = data[1];
        //???????????????
        String name = data[2];
        //????????????
        String remarkId = data[4];
        //????????????
        String createTime = data[3];
        //??????????????????
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
        //???????????????????????????
        Calendar calendar = Calendar.getInstance();
        calendar.get(Calendar.SECOND);
        SimpleDateFormat s = new SimpleDateFormat("ss");
        String second = s.format(calendar.getTime());

        createTime = createTime + ":" + second;
        //System.out.println(createTime);
        maintenancePeriod = maintenancePeriod + ":" + second;
        String remark = RemarkUtil.getInstance().remark(remarkId);
        //????????????????????????
        AddRecordDTO addRecord = AddRecordDTO.builder()
                .createTime(createTime)
                .equipmentId(equipmentId)
                .name(name)
                .remark(remark)
                .build();
        maintenanceRecordMapper.addAMaintenanceRecord(addRecord);

        //??????????????????????????????
        equipmentMapper.updateMaintenancePeriod(maintenancePeriod, equipmentId);
        okHttpUtil.postData("M,1,0,N");

    }
}
