package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Product;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddProductDTO;
import com.flushbonading.cps.entity.dto.SearchProductDTO;
import com.flushbonading.cps.entity.vo.DefectiveDataVO;
import com.flushbonading.cps.entity.vo.DiaryDataVO;
import com.flushbonading.cps.entity.vo.ProductDataVO;
import com.flushbonading.cps.entity.vo.ProductVO;
import com.flushbonading.cps.mapper.DiaryMapper;
import com.flushbonading.cps.mapper.ProductMapper;
import com.flushbonading.cps.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.text.SimpleDateFormat;
import java.util.*;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Service
public class ProductServiceImpl extends ServiceImpl<ProductMapper, Product> implements ProductService {

    /**
     * 产品映射器
     */
    @Autowired
    ProductMapper productMapper;
    @Autowired
    DiaryMapper diaryMapper;

    /**
     * 查询每一总牌号对应的生产数量
     *
     * @return 返回Map<K, V> K代表牌号，V代表数量
     */
    @Override
    public List<Map<String, Object>> getAllCountsByDifferentMaterial() {
        //构建查询构造器
        QueryWrapper<Product> queryWrapper = new QueryWrapper<>();
        //查询每总牌号的数量
        queryWrapper.select("material_id", "COUNT(1) as counts")
                .groupBy("material_id");
        List<Map<String, Object>> maps = productMapper.selectMaps(queryWrapper);
        return maps;
    }

    @Override
    public List<ProductVO> getAllProductMessage(SearchProductDTO search, Integer page) {
        return productMapper.getAllProductMessage(search, page);
    }

    @Override
    public Integer totalCounts(SearchProductDTO search) {
        return productMapper.totalCounts(search);
    }

    @Override
    public Integer totalPages(SearchProductDTO search) {
        return PageUtil.totalPage(totalCounts(search), 7);
    }

    @Override
    public RespBean deleteProductById(String id) {
        Integer deleteProductById = productMapper.deleteProductById(id);
        Validator.validateNotNull(deleteProductById, Tip.DELETE_ERROE.content());
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public RespBean insertAProduct(AddProductDTO add) {
        Integer addProduct = productMapper.insertAProduct(add);
        Validator.validateNotNull(addProduct, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public List<String> getBrandData(List<String> brandNames) {
        List<String> brandData = new ArrayList<>();
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String today = sdf.format(date);
        List<ProductDataVO> productDataVOS = productMapper.getProductMap(today);
        Map<String, String> productMap = new HashMap<>();
        for (ProductDataVO productDataVO : productDataVOS) {
            productMap.put(productDataVO.getMaterialId(), productDataVO.getCounts());
        }
        for (String brandName : brandNames) {
            if (productMap.containsKey(brandName)) {
                brandData.add(productMap.get(brandName));
            } else {
                brandData.add(0 + "");
            }
        }
        return brandData;
    }

    @Override
    public List<String> getYieldData() {
        List<DiaryDataVO> diaryDataVos = diaryMapper.getDiaryDataVos();
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String today = sdf.format(date);
        List<String> yieldDatas = new ArrayList<>();
        for (DiaryDataVO diaryDataVO : diaryDataVos) {
            int time = Integer.parseInt(diaryDataVO.getName());
            int startTime = 4 * (time - 1);
            int endTime = 4 * time;
            int yieldNumber;
            if (startTime == 0 || startTime == 4) {
                yieldNumber = productMapper.getYieldNumber(today + " 0" + startTime + ":00:00", today + " 0" + endTime + ":00:00");
            } else if (startTime == 8) {
                yieldNumber = productMapper.getYieldNumber(today + " 0" + startTime + ":00:00", today + " " + endTime + ":00:00");
            } else {
                yieldNumber = productMapper.getYieldNumber(today + " " + startTime + ":00:00", today + " " + endTime + ":00:00");
            }

            int total = diaryDataVO.getValue();
            if (total == 0) {
                yieldDatas.add("0.00");
                continue;
            }
            System.out.println("合格产品:" + yieldNumber);
            double yield = yieldNumber / (double) total * 100;
            System.out.println(yield);
            System.out.println(yield);
            String yieldData = (yield + "").substring(0, (yield + "").length());
            System.out.println("总数:" + total);
            yieldDatas.add(yieldData);
        }
        return yieldDatas;
    }

    @Override
    public List<DefectiveDataVO> getDefectiveData() {
        return productMapper.getDefectiveData();
    }
}
